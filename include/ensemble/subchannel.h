#ifndef __DABDECODE_ENSEMBLE__SUBCHANNEL
#define __DABDECODE_ENSEMBLE__SUBCHANNEL

#include <cstdint>

namespace dabdecode
  {

  struct subchannel
    {
    std::uint16_t const id;
    std::uint16_t const start;
    std::uint16_t const size;
    std::uint16_t const bitrate;
    bool const isEep;
    std::uint16_t const eepProtectionLevel;

    bool operator<(subchannel const & other) const;
    };

  }

#endif

