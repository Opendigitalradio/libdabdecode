#ifndef __DABDECODE_CONSTANTS__PUNCTURING_VECTORS
#define __DABDECODE_CONSTANTS__PUNCTURING_VECTORS

#include <array>
#include <cstdint>

/**
 * @file
 * @author Felix Morgner
 * @copyright 3-Clause-BSD
 *
 * @brief This files contains the DAB standard puncturing vectors.
 *
 * As documented in convolution_encoder_attributes.h, DAB uses convolution coding for its
 * data. Since convolution coding is associated with a rather large spacial overhead of 4
 * in DAB, puncturing is used to 'reduce' the amount of redundancy. Since both the sender and
 * receiver must use the same puncturing procedure, the vectors defined in this file are
 * used. For more information on the encoding an puncturing, refer to ETSI EN 300 401 Section 11.
 */

namespace dabdecode
  {

  namespace constants
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
    using regular_puncturing_vector_t = std::array<uint8_t, 32>;

    /**
     * @internal
     *
     * @brief The list of standard puncturing vectors.
     *
     * This list contains all standard puncturing vectors with the exception of the tail
     * puncturing vector. All puncturing vectors in this list have the same length, which
     * is guaranteed by using a std::array.
     *
     * The puncturing vectors are maintained in the exact same order as specified by the the DAB
     * standard ETSI EN 300 401 Section 11.1.2.
     *
     * @note The numbering of the vectors is offset by -1 (thus starting at 0 not 1) simply for
     * the sake of spacial efficiency.
     */
    constexpr std::array<regular_puncturing_vector_t, 24> kPuncturingVectors {{
      {{1,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0}},
      {{1,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0}},
      {{1,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0}},
      {{1,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0}},
      {{1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,0,0}},
      {{1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0}},
      {{1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,0}},
      {{1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0}},
      {{1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0}},
      {{1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0}},
      {{1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0}},
      {{1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0}},
      {{1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,0,0}},
      {{1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0}},
      {{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0}},
      {{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0}},
      {{1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0}},
      {{1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0}},
      {{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0}},
      {{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0}},
      {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0}},
      {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}},
      {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}},
      {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}
    }};

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
     * ::dabdecode::regular_puncturing_vector_t.
     */
    using tail_puncturing_vector_t = std::array<uint8_t, 24>;

    /**
     * @internal
     *
     * @brief The tail puncturing vector.
     *
     * The DAB standard defines a special vector for the puncturing of the tail bits. This vector
     * can be found in section 11 of ETSI EN 300 401.
     */
    constexpr tail_puncturing_vector_t kTailPuncturingVector {{
      1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0
    }};

    }

  }

#endif

