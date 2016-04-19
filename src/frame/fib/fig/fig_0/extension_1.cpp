#include "frame/fib/fig/fig_0/fig_0.h"
#include "ensemble/subchannel_descriptor.h"

#include <iostream>

namespace dabdecode
  {

  fig_0::extension_1::extension_1(std::vector<uint8_t> && data)
    : extension{std::move(data)}
    {
    for(auto it = m_dataField.cbegin(); it != m_dataField.cend(); ++it)
      {
      std::uint8_t subchannelId    = *it >> 2;
      std::uint16_t startAddress   = (uint16_t(*it) & 3) << 8 | *++it;
      bool uep                     = !(*++it >> 7);
      std::uint8_t tableIndex      = uep ? *it & 63 : 255;
      std::uint8_t eepOption       = uep ? 255 : *it >> 4 & 7;
      std::uint8_t protectionLevel = uep ? 255 : *it >> 2 & 3;
      std::uint16_t subchannelSize = uep ? -1  : (std::uint16_t(*it & 3) << 8) | *++it;

      descriptors.push_back(subchannel_descriptor{subchannelId, startAddress, uep, tableIndex, eepOption, protectionLevel, subchannelSize});
      }
    }

  uint8_t fig_0::extension_1::type() const
    {
    return 1;
    }

  }
