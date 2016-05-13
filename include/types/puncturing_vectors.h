#ifndef __DAB_TYPES__PUNCTURING_VECTORS
#define __DAB_TYPES__PUNCTURING_VECTORS

#include <cstdint>
#include <array>

namespace dab
  {

  namespace __internal_dabdecode
    {

    namespace types
      {

      /**
       * @internal
       *
       * @brief Type alias for a regular puncturing vector.
       *
       * This type makes it possible to easily specify when a function takes or creates a
       * puncturing vector. All puncturing vectors with the exception of the tail puncturing
       * vector are exactly 32-bit long. We use a std::array<uint8_t, 32> to make the usage
       * simpler. Additionally we do not need to synchronize access if we were to parallellize
       * code that uses these vectors.
       */
      using regular_puncturing_vector_t = std::array<std::uint8_t, 32>;

      /**
       * @internal
       *
       * @brief Type alias for the tail puncturing vector.
       *
       * This type alias makes it easy to declare functions that receive or return a puncturing
       * vector for the tail bits of a DAB codeword. The convolution encoder used in DAB has a
       * constraint length of 7, which results in 6 tail bits to clear the encoder shift registers.
       * Since DAB uses a 1/4 code, 6 input bits result in 24 output bits thus resulting in a
       * puncturing vector length of 24. For the rationale on the type choice, please refer to
       * ::regular_puncturing_vector_t.
       */
      using tail_puncturing_vector_t = std::array<std::uint8_t, 24>;

      }

    }

  }

#endif

