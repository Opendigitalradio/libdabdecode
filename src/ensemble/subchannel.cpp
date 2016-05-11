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
    std::size_t eep_first_block_count(subchannel const & subchannel)
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

    std::size_t eep_second_block_count(subchannel const & subchannel)
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

    std::size_t eep_first_puncturing_vector_idx(subchannel const & subchannel)
      {
      std::size_t idx{};

      if(!subchannel.eepProtectionTable())
        {
        switch(subchannel.eepProtectionLevel())
          {
          case 0:
            idx = 24;
            break;
          case 1:
            if(subchannel.bitrate() == 8)
              {
              idx = 13;
              }
            else
              {
              idx = 14;
              }
            break;
          case 2:
            idx = 8;
            break;
          case 3:
            idx = 3;
            break;
          }
        }
      else
        {
        switch(subchannel.eepProtectionLevel())
          {
          case 0:
            idx = 10;
            break;
          case 1:
            idx = 6;
            break;
          case 2:
            idx = 4;
            break;
          case 3:
            idx = 2;
            break;
          }
        }

      return idx - 1;
      }

    std::size_t eep_second_puncturing_vector_idx(subchannel const & subchannel)
      {
      std::size_t idx{};

      if(!subchannel.eepProtectionTable())
        {
        switch(subchannel.eepProtectionLevel())
          {
          case 0:
            idx = 23;
            break;
          case 1:
            if(subchannel.bitrate() == 8)
              {
              idx = 12;
              }
            else
              {
              idx = 13;
              }
            break;
          case 2:
            idx = 7;
            break;
          case 3:
            idx = 2;
            break;
          }
        }
      else
        {
        switch(subchannel.eepProtectionLevel())
          {
          case 0:
            idx = 9;
            break;
          case 1:
            idx = 5;
            break;
          case 2:
            idx = 3;
            break;
          case 3:
            idx = 1;
            break;
          }
        }

      return idx - 1;
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

    if(++m_processedFragments % 16)
      {
      return;
      }

    if(m_isEep)
      {
      process_eep();
      }

    }

  void subchannel::process_eep()
    {
    std::vector<float> depunctured{};
    int idx{};

    auto const firstPvIdx = eep_first_puncturing_vector_idx(*this);
    auto const secondPvIdx = eep_second_puncturing_vector_idx(*this);

    for(std::size_t block = 0; block < eep_first_block_count(*this); ++block)
      {
      for(int bit = 0; bit < 128; ++bit)
        {
        if(kPuncturingVectors[firstPvIdx][bit % 32])
          {
          depunctured.push_back(m_deinterleavedData[idx++]);
          }
        else
          {
          depunctured.push_back(0);
          }
        }
      }

    for(std::size_t block = 0; block < eep_second_block_count(*this); ++block)
      {
      for(int bit = 0; bit < 128; ++bit)
        {
        if(kPuncturingVectors[secondPvIdx][bit % 32])
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

    auto const deconvolvedLength = depunctured.size() - kEncoderInputLength * kEncoderMemorySize;
    auto deconvolved = std::unique_ptr<uint8_t[]>(new uint8_t[deconvolvedLength + kEncoderMemorySize]);

    viterbi_algorithm_combined(m_fsm.I(),
                               m_fsm.S(),
                               m_fsm.O(),
                               m_fsm.OS(),
                               m_fsm.PS(),
                               m_fsm.PI(),
                               deconvolvedLength + kEncoderMemorySize,
                               0,
                               0,
                               kEncoderOutputLength,
                               {kDecoderLookupTable.cbegin(), kDecoderLookupTable.cend()},
                               depunctured.data(),
                               deconvolved.get());

    auto scramblerRegister = std::array<uint8_t, 9>{{1, 1, 1, 1, 1, 1, 1, 1, 1}};
    auto temporary = uint8_t{};

    m_data.resize(deconvolvedLength / 8);

    for(std::size_t idx{}; idx < deconvolvedLength; ++idx)
      {
      temporary = scramblerRegister[8] ^ scramblerRegister[4];

      for(std::size_t bit{8}; bit > 0; --bit)
        {
        scramblerRegister[bit] = scramblerRegister[bit - 1];
        }

      scramblerRegister[0] = temporary;

      deconvolved[idx] ^= temporary;
      }

    for(std::size_t byteIndex{}; byteIndex < deconvolvedLength / 8; ++byteIndex)
      {
      auto byte = uint8_t{};

      for(int bit = 0; bit < 8; ++bit)
        {
        byte |= (deconvolved.get())[8 * byteIndex + bit] << (7 - bit);
        }

      m_data[byteIndex] = byte;
      }
    }

  }

