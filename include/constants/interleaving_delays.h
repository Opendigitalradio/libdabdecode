#ifndef __DAB_CONSTANTS__INTERLEAVING_DELAYS
#define __DAB_CONSTANTS__INTERLEAVING_DELAYS

#include <array>

namespace dab
  {

  namespace __internal_dabdecode
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
        15, 7, 11, 3, 13, 5, 9, 1, 14, 6, 10, 2, 12, 4, 8, 0
      }};

      }

    }

  }

#endif

