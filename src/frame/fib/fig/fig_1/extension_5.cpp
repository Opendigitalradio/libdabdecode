#include "frame/fib/fig/fig_1/fig_1.h"

namespace dabdecode
  {

  fig_1::extension_5::extension_5(uint32_t const id)
    : extension{{(uint8_t((id >> 24) & 0xFF)),
                 (uint8_t((id >> 16) & 0xFF)),
                 (uint8_t((id >>  8) & 0xFF)),
                 uint8_t(id)}},
      serviceId(id)
    {

    }

  uint8_t fig_1::extension_5::type() const
    {
    return 5;
    }

  }

