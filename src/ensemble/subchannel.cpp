#include "ensemble/subchannel.h"
#include "constants/common.h"

#include <iostream>

namespace dabdecode
  {

  using namespace constants;

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
    (void)fragmentSize;
    }

  }

