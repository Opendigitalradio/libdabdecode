#ifndef __DABDECODE_CONSTANTS__INTERLEAVING_DELAYS
#define __DABDECODE_CONSTANTS__INTERLEAVING_DELAYS

#include <array>

namespace dabdecode
  {

  namespace constants
    {

    /**
     * @internal
     *
     * @brief The time interleaving delays
     *
     * This array contains the time-interleaving delays. The bits
     * transferred in single subchannel are delayed using the order of this sequence.
     */
    constexpr std::array<std::uint8_t, 16> kInterleavingDelays{{
      0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15
    }};

    }

  }

#endif

