#include "ensemble/ensemble.h"
#include "parser/fic_parser.h"

namespace dabdecode
  {

  fic_parser::fic_parser(ensemble & target)
    : m_target{target}
    {

    }

  void fic_parser::parse(std::vector<fib> const & fic)
    {
    for(auto const & fib : fic)
      {
      auto fibBase = fib.begin();
      auto fibEnd = fib.end();

      while(fibBase != fibEnd && !(*fibBase == 255))
        {
        auto const figType = *fibBase >> 5;
        auto const figSize = *fibBase & 31;
        ++fibBase;

        switch(figType)
          {
          case 0:
            fig_0(fibBase);
            break;
          case 1:
            fig_1(fibBase);
            break;
          default:
            break;
          };

        fibBase += figSize;
        }
      }
    }

  }

