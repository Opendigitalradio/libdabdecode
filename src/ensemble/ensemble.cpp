#include "ensemble/ensemble.h"
#include "ensemble/service.h"
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

  std::uint8_t ensemble::country() const
    {
    return m_id >> 12;
    }

  std::uint16_t ensemble::reference() const
    {
    return m_id & 0xFFF;
    }

  std::set<service> const & ensemble::services() const
    {
    return m_services;
    }

  void ensemble::label(std::string const & label)
    {
    m_label = label;
    }

  void ensemble::id(std::uint16_t const id)
    {
    m_id = id;
    }

  void ensemble::add(subchannel && subchannel)
    {
    m_subchannels.insert(std::move(subchannel));
    }

  void ensemble::add(service && service)
    {
    m_services.insert(std::move(service));
    }

  void ensemble::activate(service const & service)
    {
    auto const pos = m_services.find(service);
    if(pos != m_services.cend())
      {
      auto const servicePtr = const_cast<struct service *>(&*pos);

      if(servicePtr != m_activeService)
        {
        m_activeService = servicePtr;
        }
      }
    }

  void ensemble::update()
    {
    if(next_frame())
      {
      auto const & fic = m_frame->fic();
      m_ficParser.parse(fic);
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
