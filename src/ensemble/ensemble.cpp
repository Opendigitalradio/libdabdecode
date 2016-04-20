#include "ensemble/ensemble.h"
#include "ensemble/subchannel_descriptor.h"
#include "frame/fib.h"
#include "mode/modes.h"

#include <iostream>
#include <vector>

namespace dabdecode
  {

  ensemble::ensemble(std::istream & sync, std::istream & data, transport_mode const mode)
    : m_sync{sync},
      m_data{data},
      m_mode{mode}
    {
    update();
    }

  std::string const & ensemble::label() const
    {
    return m_label;
    }

  std::uint16_t ensemble::id() const
    {
    return m_id;
    }

  void ensemble::label(std::string const & label)
    {
    m_label = label;
    }

  void ensemble::id(std::uint16_t const id)
    {
    m_id = id;
    }

  void ensemble::update()
    {
    if(next_frame())
      {
      auto fic = m_frame->fic();

      for(auto const & fib : fic)
        {
        parse_fib(fib, *this);
        }

      }
    else
      {
      m_id = 0;
      m_label = "";
      }
    }

  ensemble::operator bool() const
    {
    return m_label.size() && m_id;
    }

  bool ensemble::next_frame()
    {
    if(!m_sync || !m_data)
      {
      return false;
      }

    auto synced = '\0';
    auto extracted = std::vector<float>(sizeof(float) * frame_size(m_mode));
    auto input = reinterpret_cast<char *>(extracted.data());

    while(m_sync >> synced && !synced)
      {
      m_data.ignore(sizeof(float) * symbol_size(m_mode));
      }

    m_data.read(input, sizeof(float) * symbol_size(m_mode));

    for(std::size_t symbol{1}; symbol < frame_symbols(m_mode); ++symbol)
      {
      if(!m_data.read(input + symbol * sizeof(float) * symbol_size(m_mode), sizeof(float) * symbol_size(m_mode)))
        {
        m_frame.reset();
        return false;
        }

      if(!m_sync.ignore(1))
        {
        m_frame.reset();
        return false;
        }
      }

    m_frame = std::unique_ptr<frame>(new frame{std::move(extracted), m_mode});
    return (bool)m_frame;
    }

  }
