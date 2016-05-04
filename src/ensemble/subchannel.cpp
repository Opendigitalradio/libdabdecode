#include "ensemble/subchannel.h"
#include "constants/common.h"
#include "constants/interleaving_delays.h"
#include "viterbi/fsm.h"
#include "viterbi/core_algorithms.h"
#include "constants/convolution_encoder_attributes.h"
#include <memory>
#include "constants/puncturing_vectors.h"

#include <iostream>

namespace dabdecode
  {

  using namespace constants;

  namespace
    {
    std::size_t first_block_count(subchannel const & subchannel)
      {
      auto count = std::size_t{};

      if(subchannel.eepProtectionTable() == 0)
        {
        auto const multiple = subchannel.bitrate() / 8;

        switch(subchannel.eepProtectionLevel())
          {
          case 0:
            count = 6 * multiple - 3;
            break;
          case 1:
            if(multiple == 1)
              {
              count = 5;
              }
            else
              {
              count = 2 * multiple - 3;
              }
            break;
          case 2:
            count = 6 * multiple - 3;
            break;
          case 3:
            count = 4 * multiple - 3;
            break;
          }
        }
      else
        {
        auto const multiple = subchannel.bitrate() / 8;

        count = 24 * multiple - 3;
        }

      return count;
      }

    std::size_t second_block_count(subchannel const & subchannel)
      {
      auto count = std::size_t{};

      if(subchannel.eepProtectionTable() == 0)
        {
        auto const multiple = subchannel.bitrate() / 8;

        switch(subchannel.eepProtectionLevel())
          {
          case 0:
            count = 3;
            break;
          case 1:
            if(multiple == 1)
              {
              count = 1;
              }
            else
              {
              count = 4 * multiple + 3;
              }
            break;
          case 2:
            count = 3;
            break;
          case 3:
            count = 2 * multiple + 3;
            break;
          }
        }
      else
        {
        count = 3;
        }

      return count;
      }
    }

  subchannel::subchannel(std::uint16_t const id, std::uint16_t const start, std::uint16_t const size,
                         std::uint16_t const bitrate, bool const isEep, std::uint16_t const eepProtectionLevel)
    : m_id{id},
      m_start{start},
      m_size{size},
      m_bitrate{bitrate},
      m_isEep{isEep},
      m_eepProtectionLevel(eepProtectionLevel & 0x00FF),
      m_eepProtectionTable(eepProtectionLevel & 0xFF00 >> 8),
      m_deinterleavedData(size * constants::kCuBits)
    {

    }

  bool subchannel::operator<(subchannel const & other) const
    {
    return m_id < other.m_id;
    }

  bool subchannel::operator==(subchannel const & other) const
    {
    return m_id == other.m_id;
    }

  std::uint16_t subchannel::id() const
    {
    return m_id;
    }

  std::uint16_t subchannel::start() const
    {
    return m_start;
    }

  std::uint16_t subchannel::size() const
    {
    return m_size;
    }

  std::uint16_t subchannel::bitrate() const
    {
    return m_bitrate;
    }

  bool subchannel::isEep() const
    {
    return m_isEep;
    }

  std::uint8_t subchannel::eepProtectionLevel() const
    {
    return m_eepProtectionLevel;
    }

  std::uint8_t subchannel::eepProtectionTable() const
    {
    return m_eepProtectionTable;
    }

  std::vector<std::uint8_t> const & subchannel::data() const
    {
    return m_data;
    }

  void subchannel::process(std::vector<float>::const_iterator samplesStart, std::vector<float>::const_iterator samplesEnd)
    {
    auto const fragmentSize = std::distance(samplesStart, samplesEnd);
    auto const fragmentBit = kInterleavingDelays[m_processedFragments];

    for(int block = 0; block < fragmentSize / 16; ++block)
      {
      m_deinterleavedData[block * 16 + fragmentBit] = *(samplesStart + block * 16 + fragmentBit);
      }

    if(++m_processedFragments < 16)
      {
      return;
      }
    else
      {
      m_processedFragments = 0;
      }

    std::vector<float> depunctured{};
    int idx{};

    for(std::size_t block = 0; block < first_block_count(*this); ++block)
      {
      for(int bit = 0; bit < 128; ++bit)
        {
        if(kPuncturingVectors[23][bit % 32])
          {
          depunctured.push_back(m_deinterleavedData[idx++]);
          }
        else
          {
          depunctured.push_back(0);
          }
        }
      }

    for(std::size_t block = 0; block < second_block_count(*this); ++block)
      {
      for(int bit = 0; bit < 128; ++bit)
        {
        if(kPuncturingVectors[22][bit % 32])
          {
          depunctured.push_back(m_deinterleavedData[idx++]);
          }
        else
          {
          depunctured.push_back(0);
          }
        }
      }

    for(int i = 0; i < 24; ++i)
      {
      if(kTailPuncturingVector[i])
        {
        depunctured.push_back(m_deinterleavedData[idx++]);
        }
      else
        {
        depunctured.push_back(0);
        }
      }

    auto deconvolved = std::unique_ptr<uint8_t[]>(new uint8_t[768 + 6]);
      viterbi_algorithm_combined(m_fsm.I(),
                                 m_fsm.S(),
                                 m_fsm.O(),
                                 m_fsm.OS(),
                                 m_fsm.PS(),
                                 m_fsm.PI(),
                                 768 + 6,
                                 0,
                                 0,
                                 4,
                                 {kDecoderLookupTable.cbegin(), kDecoderLookupTable.cend()},
                                 depunctured.data(),
                                 deconvolved.get());

    auto scramblerRegister = std::array<uint8_t, 9>{{1, 1, 1, 1, 1, 1, 1, 1, 1}};
    auto temporary = uint8_t{};

    for(std::size_t idx{}; idx < 768; ++idx)
      {
      temporary = scramblerRegister[8] ^ scramblerRegister[4];

      for(std::size_t bit{8}; bit > 0; --bit)
        {
        scramblerRegister[bit] = scramblerRegister[bit - 1];
        }

      scramblerRegister[0] = temporary;

      deconvolved[idx] ^= temporary;
      }

    for(int i = 0; i < 768 / 8; ++i)
      {
      auto byte = uint8_t{};

      for(int bit = 0; bit < 8; ++bit)
        {
        byte |= (deconvolved.get())[8 * i + bit] << (7 - bit);
        }

      m_data.push_back(byte);
      }
    }

  }

