#include "constants/puncturing_vectors.h"
#include "frame/fib.h"
#include "frame/frame.h"
#include "mode/modes.h"
#include "viterbi/core_algorithms.h"

#include <memory>
#include <stdexcept>
#include <string>

namespace dabdecode
  {

  namespace
    {

    std::vector<float> depuncture_fic_codeword(std::vector<float> && codeword, transport_mode const mode)
      {
      using namespace constants;

      std::vector<float> depunctured(punctured_codeword_size(mode) * 4 / 3 + 24);
      auto inputIndex = std::size_t{};
      auto outputIndex = std::size_t{};

      auto const nofFirstBlocks = mode == transport_mode::mode_3 ? 29 : 21;
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

    void descramble_fic_codeword(std::vector<uint8_t> & scrambled, transport_mode const mode)
      {
      auto scramblerRegister = std::array<uint8_t, 9>{{1, 1, 1, 1, 1, 1, 1, 1, 1}};
      auto const ficCodewordSize = fic_codeword_size(mode);
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

  frame::frame(std::vector<float> && data, transport_mode const mode)
    : m_data{std::move(data)},
      m_mode{mode}
    {
    if(m_data.size() != frame_size(m_mode) * sizeof(float))
      {
      throw std::runtime_error{std::string{"Invalid data length "} + std::to_string(m_data.size())};
      }

    extract_fic_codewords();
    }

  std::vector<fib> frame::fic()
    {
    std::vector<fib> fic{};

    for(auto const & cw : m_ficCodewords)
      {
      for(std::size_t fibIdx{}; fibIdx < fibs_in_codeword(m_mode); ++fibIdx)
        {
        fic.emplace_back(cw.cbegin() + fibIdx * 32, cw.cbegin() + (fibIdx + 1) * 32);
        }
      }

    return fic;
    }

  void frame::extract_fic_codewords()
    {
    using namespace constants;

    auto const puncturedCodewordSize = punctured_codeword_size(m_mode);
    auto const ficSize = fic_size(m_mode);
    auto nofCodewords = ficSize / puncturedCodewordSize;

    auto beginIterator = m_data.cbegin();
    auto endIterator = m_data.cbegin() + puncturedCodewordSize;

    for(auto index = std::size_t{}; index < nofCodewords; ++index)
      {
      auto depunctured = depuncture_fic_codeword({beginIterator, endIterator}, m_mode);
      auto deconvolved = std::unique_ptr<uint8_t[]>(new uint8_t[fic_codeword_size(m_mode) + 6]);

      viterbi_algorithm_combined(m_fsm.I(),
                                 m_fsm.S(),
                                 m_fsm.O(),
                                 m_fsm.OS(),
                                 m_fsm.PS(),
                                 m_fsm.PI(),
                                 fic_codeword_size(m_mode) + 6,
                                 0,
                                 0,
                                 4,
                                 {kDecoderLookupTable.cbegin(), kDecoderLookupTable.cend()},
                                 depunctured.data(),
                                 deconvolved.get());

      m_ficCodewords.emplace_back(deconvolved.get(), deconvolved.get() + fic_codeword_size(m_mode));
      descramble_fic_codeword(m_ficCodewords.back(), m_mode);
      assemble_bytes(m_ficCodewords.back());

      beginIterator += puncturedCodewordSize;
      endIterator = beginIterator + puncturedCodewordSize;
      }
    }

  }

