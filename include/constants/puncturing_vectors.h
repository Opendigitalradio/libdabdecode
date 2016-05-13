#ifndef __DAB_CONSTANTS__PUNCTURING_VECTORS
#define __DAB_CONSTANTS__PUNCTURING_VECTORS

#include "types/puncturing_vectors.h"

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

namespace dab
  {

  namespace __internal_dabdecode
    {

    namespace constants
      {

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
      constexpr std::array<types::regular_puncturing_vector_t, 24> kPuncturingVectors {{
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
       * @brief The tail puncturing vector.
       *
       * The DAB standard defines a special vector for the puncturing of the tail bits. This vector
       * can be found in section 11 of ETSI EN 300 401.
       */
      constexpr types::tail_puncturing_vector_t kTailPuncturingVector {{
        1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0
      }};

      }

    }

  }

#endif

