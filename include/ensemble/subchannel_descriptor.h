#ifndef __DABDECODE_ENSEMBLE__SUBCHANNEL_DESCRIPTOR
#define __DABDECODE_ENSEMBLE__SUBCHANNEL_DESCRIPTOR

#include <cstdint>

namespace dabdecode
  {

  struct subchannel_descriptor
    {
    uint8_t const id;
    uint16_t const start;
    bool const usesUep;
    uint8_t const tableIndex;
    uint8_t const eepOption;
    uint8_t const protectionLevel;
    uint16_t const subchannelSize;
    };

  }

#endif

