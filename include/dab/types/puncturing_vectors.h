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

#ifndef DABDECODE_TYPES_PUNCTURING_VECTORS
#define DABDECODE_TYPES_PUNCTURING_VECTORS

#include <cstdint>
#include <array>

namespace dab
  {

  namespace internal
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

