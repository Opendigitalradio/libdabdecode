#include "ensemble/ensemble.h"
#include "frame/fib/fib.h"
#include "frame/fib/fig/figs.h"
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

  std::string const & ensemble::name() const
    {
    return m_name;
    }

  std::uint16_t ensemble::id() const
    {
    return m_id;
    }

  void ensemble::update()
    {
    if(next_frame())
      {
      for(auto const & fib : m_frame->fic())
        {
        for(auto const & fig : fib.figs())
          {
          if(fig)
            {
            fig->dispatch(*this);
            }
          }
        }
      }
    else
      {
      m_id = 0;
      m_name = "";
      }
    }

  ensemble::operator bool() const
    {
    return m_name.size() && m_id;
    }

  bool ensemble::next_frame()
    {
    if(!m_sync || !m_data)
      {
      return false;
      }

    auto symbol_size = 1536 * 2;

    auto synced = '\0';
    auto extracted = std::vector<float>(sizeof(float) * frame_size(m_mode));
    auto input = reinterpret_cast<char *>(extracted.data());

    while(m_sync >> synced && !synced)
      {
      m_data.ignore(sizeof(float) * symbol_size);
      }

    m_data.read(input, sizeof(float) * symbol_size);

    for(std::size_t symbol{1}; symbol < 75; ++symbol)
      {
      if(!m_data.read(input + symbol * sizeof(float) * symbol_size, sizeof(float) * symbol_size))
        {
        m_frame.reset();
        return false;
        }

      if(!m_sync.ignore(sizeof(synced)))
        {
        m_frame.reset();
        return false;
        }
      }

    m_frame = std::unique_ptr<frame>(new frame{std::move(extracted), m_mode});
    return (bool)m_frame;
    }

  void ensemble::handle(fig_0 const &)
    {

    }

  void ensemble::handle(fig_1 const & label)
    {
    if(auto extension = label.ext())
      {
      switch(extension->type())
        {
        case 0:
          m_id = ((fig_1::extension_0 const *)extension)->ensembleId;
          m_name = static_cast<std::string>(label);
          break;
        default:
          break;
        }
      }
    }

  }
