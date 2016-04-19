#include "frame/fib/fig/fig_0/fig_0.h"

namespace dabdecode
  {

  fig_0::extension_0::extension_0(std::vector<uint8_t> const & data)
    : extension{{data.cbegin(), data.cend()}},
      countryId(data[0] >> 4),
      ensembleId(((uint16_t)data[0]) << 8 | data[1]),
      change(data[2] >> 6),
      hasAlarm((data[2] >> 5) & 1),
      cifCountHigh(data[2] & 0x1f),
      cifCountLow(data[3]),
      occcurenceChange(change ? data[4] : 0)
    {

    }

  uint8_t fig_0::extension_0::type() const
    {
    return 0;
    }

  }

