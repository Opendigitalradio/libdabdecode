#include "util/hex_encode.h"

#include <array>

namespace dabdecode
  {

  namespace
    {

    std::array<char, 16> constexpr nibbleTable {{
      '0', '1', '2', '3',
      '4', '5', '6', '7',
      '8', '9', 'a', 'b',
      'c', 'd', 'e', 'f',
    }};

    }

  std::string hex_encode(std::vector<uint8_t> const & data)
    {
    auto buffer = std::string{};
    buffer.resize(data.size() * 5);

    for(std::size_t idx{}; idx < data.size(); idx++)
      {
      buffer[5 * idx] = '0';
      buffer[5 * idx + 1] = 'x';
      buffer[5 * idx + 2] = nibbleTable[(data[idx] >> 4) & 0xf];
      buffer[5 * idx + 3] = nibbleTable[data[idx] & 0xf];
      buffer[5 * idx + 4] = ' ';
      }

    return buffer;
    }

  }

