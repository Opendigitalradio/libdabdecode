#include "ensemble/ensemble.h"
#include "parser/fic_parser.h"

#include <cstdint>

namespace dabdecode
  {

  void fic_parser::fig_0(fic_parser::iterator const & base)
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


  }

