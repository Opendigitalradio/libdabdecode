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

#ifndef DABDECODE_FRAME_FIB
#define DABDECODE_FRAME_FIB

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <vector>

namespace dab
  {

  namespace internal
    {

    /**
     * @internal
     * @author Felix Morgner
     *
     * @brief This class represents a Fast Information Block (FIB)
     *
     * A FIB contains a number of Fast Information Groups (FIGs) which provide information
     * of the ensemble itself as well as the structure und information related to the different
     * services carried in an ensemble.
     *
     * This class is designed as an overlay. It only stores iterators marking the
     * begin and end of the range of bytes that make up a FIB. The creator/user must thus guarantee
     * that the range remains valid while the FIB is in use.
     */
    struct fib
      {
      using iterator = std::vector<std::uint8_t>::const_iterator;

      fib(iterator const & begin, iterator const & end);

      operator bool() const;

      iterator begin() const;
      iterator end() const;

      private:
        iterator const m_begin;
        iterator const m_end;
      };

    }

  }

#endif
