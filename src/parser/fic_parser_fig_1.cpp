#include "ensemble/ensemble.h"
#include "parser/fic_parser.h"

#include <cstdint>

namespace dabdecode
  {

  void fic_parser::fig_1(fic_parser::iterator const & base)
    {
    auto isOther = bool(*base >> 3 & 1);
    auto extension = *base & 7;

    if(!isOther)
      {
      switch(extension)
        {
        case 0:
          fig_1_ext_0(base + 1);
          break;
        default:
          break;
        }
      }

    }

  void fic_parser::fig_1_ext_0(fic_parser::iterator const & base)
    {
    auto ensembleId = std::uint16_t(*base) << 8 | *(base + 1);

    if(m_target.id() == ensembleId)
      {
      m_target.label({base + 2, base + 18});
      }
    }

  }

