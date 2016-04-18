#include "frame/fib/fig/fig_1/fig_1.h"

namespace dabdecode
  {

  fig_1::extension_0::extension_0(uint16_t const id)
    : extension{{(uint8_t((id >> 8) & 0xFF)), uint8_t(id)}},
      ensembleId(id)
    {

    }

  }

