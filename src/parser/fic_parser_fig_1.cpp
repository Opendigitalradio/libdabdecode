#include "ensemble/ensemble.h"
#include "parser/fic_parser.h"

#include <literals/binary_literal.h>

#include <cstdint>

namespace dab
  {

  using namespace __internal_common::literals;

  namespace __internal_dabdecode
    {

    void fic_parser::fig_1(fic_parser::iterator const & base)
      {
      auto isOther = bool(*base >> 3 & 1_b);
      auto extension = *base & 111_b;

      if(!isOther)
        {
        switch(extension)
          {
          case 0:
            fig_1_ext_0(base + 1);
            break;
          case 5:
            fig_1_ext_5(base + 1);
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

    void fic_parser::fig_1_ext_5(fic_parser::iterator const & base)
        {
        auto serviceId = *base << 24 | *(base + 1) << 16 | *(base + 2) << 8 | *(base + 3);
        auto service = m_target.m_services.find(serviceId);

        if(service != m_target.m_services.cend() && service->second)
          {
          service->second->label({base + 4, base + 20});
          }
        }

    }

  }

