#include "frame/fib.h"
#include "ensemble/ensemble.h"

namespace dabdecode
  {

  namespace
    {

    void fig_0_extension_0(fib::iterator const start, ensemble & target)
      {
      auto ensembleId = uint16_t{*start} << 8 | *(start + 1);

      target.id(ensembleId);
      }

    void fig_0(fib::iterator const & start, ensemble & target)
      {
      auto extension = *start & 31;

      switch(extension)
        {
        case 0:
          fig_0_extension_0(start + 1, target);
          break;
        default:
          break;
        }
      }

    void fig_1_extension_0(fib::iterator const & start, ensemble & target)
      {
      auto ensembleId = uint16_t{*start} << 8 | *(start + 1);

      if(ensembleId == target.id())
        {
        target.label({start + 1, start + 1 + 16});
        }
      }

    void fig_1(fib::iterator const & start, ensemble & target)
      {
      auto isOther = bool(*start >> 3 & 1);
      auto extension = *start & 7;

      switch(extension)
        {
        case 0:
          if(!isOther)
            {
            fig_1_extension_0(start + 1, target);
            }

          break;
        default:
          break;
        }
      }

    }

  void parse_fib(fib const & block, ensemble & target)
    {
    auto fibPos = block.begin();
    auto fibEnd = block.end();

    while(fibPos != fibEnd)
      {
      auto const type = *fibPos >> 5;
      auto const size = *fibPos & 31;
      ++fibPos;

      switch(type)
        {
        case 7:
          if(size == 31)
            {
            return;
            }
          break;
        case 0:
          fig_0(fibPos, target);
          break;
        case 1:
          fig_1(fibPos, target);
          break;
        default:
          break;
        }

      fibPos += size;
      }
    }

  }

