#ifndef __DABDECODE_UTIL__HEX_ENCODE
#define __DABDECODE_UTIL__HEX_ENCODE

#include <cstdint>
#include <string>
#include <vector>

namespace dabdecode
  {

  std::string hex_encode(std::vector<uint8_t> const & data);

  }

#endif

