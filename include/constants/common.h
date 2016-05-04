#ifndef __DABDECODE_CONSTANTS__COMMON
#define __DABDECODE_CONSTANTS__COMMON

#include <cstdint>

namespace dabdecode
  {

  namespace constants
    {

    /**
     * @internal
     *
     * @brief The size of a Capacity Unit (CU) in bits
     *
     * Each Common Interleaved Frame (CIF) is made up of a certain number
     * of Capacity Units (CUs). A CU is the smallest addressable unit of
     * a CIF. The size of a CU does not depend on the current transmission
     * mode.
     */
    constexpr std::uint8_t kCuBits = 64;

    /**
     * @internal
     *
     * @brief The number of Capacity Units (CUs) in a Common Interleaved Frame (CIF)
     *
     * Each Common Interleaved Frame (CIF) consists of a fixed number of
     * Capacity Units (CUs). The number of CUs per CIF is constant across
     * all transmission modes.
     */
    constexpr std::uint16_t kCusPerCif = 864;

    }

  }

#endif

