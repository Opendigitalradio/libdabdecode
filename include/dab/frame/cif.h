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

#ifndef DABDECODE_FRAME_CIF
#define DABDECODE_FRAME_CIF

#include <cstdint>
#include <vector>

namespace dab
  {

  namespace internal
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

    /**
     * @internal
     *
     * @brief This class represents a Common Interleaved Frame (CIF)
     *
     * A CIF conatains the Capacity Units (CUs) which in turn contain the data that
     * is being transported in different subchannels. The subchannel data is
     * time-interleaved thus the I in CIF.
     *
     * This calls is designed as an overlay. It only stores iterators
     * marking the begin and end of the range of bytes that represent a CIF. The creator/user
     * must guarantee that the ramge remains valid while the CIF is in use.
     *
     * @note Contrary to a @ref fib which is an overlay for already decoded bytes, the CIF is an
     * overlay for non-decoded samples since decoding can only happen in conjunction with the
     * information of a @ref subchannel.
     */
    struct cif
      {
      using iterator = std::vector<float>::const_iterator;

      cif(iterator const & begin, iterator const & end);

      iterator begin() const;
      iterator end() const;

      private:
        iterator const m_begin;
        iterator const m_end;
      };

    }

  }

#endif
