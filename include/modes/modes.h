#ifndef __DABDECODE_MODES__MODES
#define __DABDECODE_MODES__MODES

#include "modes/basic_mode.h"

/*
  template<std::size_t Carriers,
           std::size_t FrameSymbols,
           std::size_t FicSymbols,
           std::size_t FrameFibs,
           std::size_t FrameCifs>
           */

namespace dabdecode
  {

  using mode_1 = basic_mode<1536,  75, 3, 12, 4>;
  using mode_2 = basic_mode< 384,  75, 3,  3, 1>;
  using mode_3 = basic_mode< 192, 152, 8,  4, 1>;
  using mode_4 = basic_mode< 768,  75, 3,  6, 2>;

  }

#endif

