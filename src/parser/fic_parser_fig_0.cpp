#include "constants/channel_size_tables.h"
#include "ensemble/ensemble.h"
#include "parser/fic_parser.h"

#include <cstdint>

namespace dabdecode
  {

  void fic_parser::fig_0(fic_parser::iterator const & base, fic_parser::iterator const & end)
    {
    auto isOther = *base >> 6 & 1;
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
        m_target.add({subchannelId, startAddress, descriptor.size, descriptor.bitrate, false, 0});
        }
      else
        {
        auto const option = *pos >> 4 & 7;
        auto const protection = *pos >> 2 & 3;
        auto const size = std::uint16_t((std::uint16_t(*pos & 3) << 8) + *++pos);
        m_target.add({subchannelId, startAddress, size, constants::eep_table_bitrate(option, size, protection),
                      true, std::uint16_t(option << 8 | protection)});
        }

      }
    }


  }

