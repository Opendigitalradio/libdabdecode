#include "constants/common.h"
#include "ensemble/ensemble.h"
#include "ensemble/service.h"
#include "frame/cif.h"
#include "frame/fib.h"
#include "mode/modes.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace dabdecode
  {

  using namespace constants;

  ensemble::ensemble(std::istream & sync, std::istream & data, transmission_mode const mode)
    : m_sync{sync},
      m_data{data},
      m_mode{mode}
    {
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

  void ensemble::add(service_component && component)
    {
    m_components.insert(std::move(component));
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

  bool ensemble::update()
    {
    if(next_frame())
      {
      auto const & fic = m_frame->fic();
      m_ficParser.parse(fic);

      if(m_activeService)
        {
        auto const primaryComponent = m_activeService->primary();
        subchannel * selected = nullptr;

        for(auto & component : m_components)
          {
          if(component.id() == primaryComponent)
            {
            auto const subchannel = component.subchannel();
            auto realSubchannel = m_subchannels.find(dabdecode::subchannel(subchannel, 0, 0, 0, false, 0));

            if(realSubchannel != m_subchannels.cend())
              {
              selected = const_cast<struct subchannel *>(&*realSubchannel);
              break;
              }
            }
          }

        if(selected)
          {
          auto const start = selected->start();
          auto const end = start + selected->size();

          for(auto const & cif : m_frame->msc())
            {
            selected->process(cif.begin() + start * kCuBits, cif.begin() + end * kCuBits);
            }
          }
        }

      return true;
      }
    else
      {
      m_id = 0;
      m_label = "";
      return false;
      }
    }

  ensemble::operator bool() const
    {
    return m_label.size() && m_id;
    }

  std::pair<constants::transport_mechanism, std::vector<std::uint8_t>> ensemble::active_data()
    {
    std::vector<std::uint8_t> data{};

    if(!m_activeService)
      {
      return std::make_pair(constants::transport_mechanism::stream_audio, data);
      }

    auto const serviceComponent = std::find_if(m_components.cbegin(), m_components.cend(), [&](service_component const & comp){
      return comp.id() == m_activeService->primary();
      });

    if(serviceComponent == m_components.cend())
      {
      return std::make_pair(constants::transport_mechanism::stream_audio, data);
      }

    auto const subchannel = std::find_if(m_subchannels.cbegin(), m_subchannels.cend(), [&](struct subchannel const & sub){
      return sub.id() == serviceComponent->subchannel();
      });

    if(subchannel == m_subchannels.cend())
      {
      return std::make_pair(constants::transport_mechanism::stream_audio, data);
      }

    return std::make_pair(serviceComponent->transport(), subchannel->data());
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
