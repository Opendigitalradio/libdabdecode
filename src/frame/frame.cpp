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

#include "dab/constants/puncturing_vectors.h"
#include "dab/frame/cif.h"
#include "dab/frame/fib.h"
#include "dab/frame/frame.h"
#include "dab/viterbi/core_algorithms.h"

#include <dab/constants/transmission_modes.h>

#include <memory>
#include <stdexcept>
#include <string>

namespace dab
  {

  using namespace internal::types;
  using namespace internal::constants;

  namespace internal
    {

    namespace
      {

      std::vector<float> depuncture_fic_codeword(std::vector<float> && codeword, transmission_mode const & mode)
        {
        std::vector<float> depunctured(mode.punctured_codeword_size * 4 / 3 + 24);
        auto inputIndex = std::size_t{};
        auto outputIndex = std::size_t{};

        auto const nofFirstBlocks = mode.id == kTransmissionMode3.id ? 29 : 21;
        auto const nofSecondBlocks = 3;
        auto const nofTailBits = 24;

        for(auto block = 0; block < nofFirstBlocks; ++block)
          {
          for(auto subblock = 0; subblock < 4; ++subblock)
            {
            for(auto bit = 0; bit < 32; ++bit)
              {
              depunctured[outputIndex++] = kPuncturingVectors[15][bit] ? codeword[inputIndex++] : 0;
              }
            }
          }

        for(auto block = 0; block < nofSecondBlocks; ++block)
          {
          for(auto subblock = 0; subblock < 4; ++subblock)
            {
            for(auto bit = 0; bit < 32; ++bit)
              {
              depunctured[outputIndex++] = kPuncturingVectors[14][bit] ? codeword[inputIndex++] : 0;
              }
            }
          }

        for(auto bit = 0; bit < nofTailBits; ++bit)
          {
          depunctured[outputIndex++] = kTailPuncturingVector[bit] ? codeword[inputIndex++] : 0;
          }

        return depunctured;
        }

      void descramble_fic_codeword(std::vector<uint8_t> & scrambled, transmission_mode const & mode)
        {
        auto scramblerRegister = std::array<uint8_t, 9>{{1, 1, 1, 1, 1, 1, 1, 1, 1}};
        auto const ficCodewordSize = mode.fib_codeword_bits;
        auto temporary = uint8_t{};

        for(std::size_t idx{}; idx < ficCodewordSize; ++idx)
          {
          temporary = scramblerRegister[8] ^ scramblerRegister[4];

          for(std::size_t bit{8}; bit > 0; --bit)
            {
            scramblerRegister[bit] = scramblerRegister[bit - 1];
            }

          scramblerRegister[0] = temporary;

          scrambled[idx] ^= temporary;
          }
        }

      void assemble_bytes(std::vector<uint8_t> & bits)
        {
        for(std::size_t byteIdx{}; byteIdx < bits.size() / 8; ++byteIdx)
          {
          auto byte = uint8_t{};

          for(int bit{}; bit < 8; ++bit)
            {
            byte |= bits[8 * byteIdx + bit] << (7 - bit);
            }

          bits[byteIdx] = byte;
          }

        bits.resize(bits.size() / 8);
        }

      }

    frame::frame(std::vector<float> && data, transmission_mode const & mode)
      : m_data{std::move(data)},
        m_mode{mode},
        m_fsm{kEncoderInputLength,kEncoderOutputLength, kEncoderPolynomials}
      {
      if(m_data.size() != m_mode.symbol_bits * m_mode.frame_symbols)
        {
        throw std::runtime_error{std::string{"Invalid data length "} + std::to_string(m_data.size())};
        }

      extract_fic_codewords();
      }

    std::vector<fib> frame::fic()
      {
      std::vector<fib> fic{};

      for(auto & cw : m_ficCodewords)
        {
        for(std::size_t fibIdx{}; fibIdx < m_mode.fib_codeword_bits / 256; ++fibIdx)
          {
          cw[fibIdx * 32 + 30] = ~cw[fibIdx * 32 + 30];
          cw[fibIdx * 32 + 31] = ~cw[fibIdx * 32 + 31];

          auto fibStart = cw.begin() + fibIdx * 32;
          auto fibEnd = fibStart + 32;
          auto readFib = fib{fibStart, fibEnd};

          if(readFib)
            {
            fic.push_back(std::move(readFib));
            }
          }

        }

      return fic;
      }

    std::vector<cif> frame::msc() const
      {
      auto msc = std::vector<cif>{};
      auto pos = m_data.cbegin() + (m_mode.fic_symbols) * m_mode.symbol_bits;

      for(std::size_t index{}; index < m_mode.frame_cifs; ++index)
        {
        msc.push_back(cif{pos + index * kCusPerCif * kCuBits, pos + (index + 1) * kCusPerCif * kCuBits});
        }

      return msc;
      }

    void frame::extract_fic_codewords()
      {
      using namespace constants;

      auto const puncturedCodewordSize = m_mode.punctured_codeword_size;
      auto const ficSize = m_mode.fic_symbols * m_mode.symbol_bits;
      auto nofCodewords = ficSize / puncturedCodewordSize;

      auto beginIterator = m_data.cbegin();
      auto endIterator = m_data.cbegin() + puncturedCodewordSize;

      for(auto index = 0; index < nofCodewords; ++index)
        {
        auto depunctured = depuncture_fic_codeword({beginIterator, endIterator}, m_mode);
        auto deconvolved = std::unique_ptr<uint8_t[]>(new uint8_t[m_mode.fib_codeword_bits + 6]);

        viterbi_algorithm_combined(m_fsm.I(),
                                   m_fsm.S(),
                                   m_fsm.O(),
                                   m_fsm.OS(),
                                   m_fsm.PS(),
                                   m_fsm.PI(),
                                   m_mode.fib_codeword_bits + 6,
                                   0,
                                   0,
                                   4,
                                   depunctured.data(),
                                   deconvolved.get());

        auto cw = std::vector<uint8_t>{deconvolved.get(), deconvolved.get() + m_mode.fib_codeword_bits};
        descramble_fic_codeword(cw, m_mode);
        assemble_bytes(cw);
        m_ficCodewords.push_back(std::move(cw));

        beginIterator += puncturedCodewordSize;
        endIterator = beginIterator + puncturedCodewordSize;
        }
      }

    }

  }

