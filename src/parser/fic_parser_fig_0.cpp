#include "constants/channel_size_tables.h"
#include "ensemble/ensemble.h"
#include "parser/fic_parser.h"
#include "ensemble/service.h"
#include "ensemble/service_component.h"

#include <cstdint>
#include <iostream>

namespace dab
  {

  namespace __internal_dabdecode
    {

    void fic_parser::fig_0(fic_parser::iterator const & base, fic_parser::iterator const & end)
      {
      auto isOther = bool(*base >> 6 & 1);
      auto isData = bool(*base >> 5 & 1);
      auto extension = *base & 31;

      if(!isOther)
        {
        switch(extension)
          {
          case 0:
            fig_0_ext_0(base + 1);
            break;
          case 1:
            fig_0_ext_1(base + 1, end);
            break;
          case 2:
            fig_0_ext_2(base + 1, end, isData);
            break;
          case 3:
            fig_0_ext_3(base + 1, end);
            break;
          default:
            break;
          }
        }
      }

    void fic_parser::fig_0_ext_0(fic_parser::iterator const & base)
      {
      auto ensembleId = std::uint16_t(*base) << 8 | *(base + 1);

      m_target.id(ensembleId);
      }

    void fic_parser::fig_0_ext_1(fic_parser::iterator const & base, fic_parser::iterator const & end)
      {
      for(auto pos = base; pos != end; ++pos)
        {
        auto const subchannelId = std::uint16_t(*pos >> 2);
        auto const startAddress = std::uint16_t(std::uint16_t(*pos & 3) << 8 | *++pos);
        auto const isLongForm = bool(*++pos >> 7);

        if(!isLongForm)
          {
          auto const descriptor = constants::kUepSubchannelDescriptors[*pos & 63];
          auto subchannel = subchannel::make(subchannelId, startAddress, descriptor.size, descriptor.bitrate, false, 0);
          m_target.add(subchannel);
          }
        else
          {
          auto const option = *pos >> 4 & 7;
          auto const protection = *pos >> 2 & 3;
          auto const size = std::uint16_t((std::uint16_t(*pos & 3) << 8) + *++pos);
          auto const subchannel = subchannel::make(subchannelId, startAddress, size,
                                                   constants::eep_table_bitrate(option, size, protection), true,
                                                   std::uint16_t(option << 8 | protection));
          m_target.add(subchannel);
          }

        }
      }

    void fic_parser::fig_0_ext_2(fic_parser::iterator const & base, fic_parser::iterator const & end, bool isData)
      {
      for(auto pos = base; pos != end; ++pos)
        {
        auto const serviceId = isData ? std::uint32_t(*pos << 24)   |
                                        std::uint32_t(*(pos + 1) << 16) |
                                        std::uint32_t(*(pos + 2) << 8)  |
                                        *(pos + 3)
                                      : std::uint16_t(*pos << 8) |
                                        *(pos + 1);

        if(isData)
          {
          pos += 3;
          }
        else
          {
          ++pos;
          }

        auto const isLocal = bool(*++pos >> 7 & 1);
        auto const nofScs  = *pos & 15;

        auto srv = service::make(serviceId, isLocal);
        srv->type(isData ? service_type::data : service_type::programme);

        for(auto scIndex = 0; scIndex < nofScs; ++scIndex)
          {
          auto const transportMechanism = transport_mechanism(*++pos >> 6);
          auto const isPrimary = bool(*(pos + 1) >> 1 & 1);

          auto component = service_component::make(std::uint16_t(std::uint16_t(*pos & 63) << 6 | *(pos + 1) >> 2),
                                                   transportMechanism, isPrimary, bool(*(pos + 1) & 1));
          m_target.add(component);
          srv->add(component);

          if(isPrimary)
            {
            srv->primary(component);
            }

          pos += 1;
          }

        m_target.add(srv);
        }
      }

    void fic_parser::fig_0_ext_3(fic_parser::iterator const & base, fic_parser::iterator const & end)
      {
      for(auto pos = base; pos != end;)
        {
        auto const componentId = std::uint16_t(*pos << 8 | *(pos + 1) >> 4);
        ++pos;

        auto const hasCaOrg = bool(*pos & 1);
        ++pos;

        auto const componentType = std::uint8_t(*pos & 63);
        ++pos;

        auto const subchannelId = std::uint8_t(*pos >> 2);
        ++pos;

        if(hasCaOrg)
          {
          pos += 2;
          }
        else
          {
          ++pos;
          }

        for(auto & component : m_target.m_components)
          {
          if(component.second->id() == componentId)
            {
            if(m_target.m_subchannels.find(subchannelId) != m_target.m_subchannels.end())
              {
              component.second->subchannel(m_target.m_subchannels[subchannelId]);
              component.second->type(componentType);
              }
            }
          }

        }

      }

    }

  }

