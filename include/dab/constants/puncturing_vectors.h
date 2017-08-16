/*
 * Copyright (C) 2017 Opendigitalradio (http://www.opendigitalradio.org/)
 * Copyright (C) 2017 Felix Morgner <felix.morgner@hsr.ch>
 * Copyright (C) 2017 Tobias Stauber <tobias.stauber@hsr.ch>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DABDECODE_CONSTANTS_PUNCTURING_VECTORS
#define DABDECODE_CONSTANTS_PUNCTURING_VECTORS

#include "dab/types/puncturing_vectors.h"

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

  namespace internal
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

