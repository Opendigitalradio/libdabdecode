#ifndef __DABDECODE_MODE__TRANSPORT_MODE
#define __DABDECODE_MODE__TRANSPORT_MODE

#include <cstdint>

namespace dabdecode
  {

  enum struct transport_mode : uint8_t
    {
    mode_1,
    mode_2,
    mode_3,
    mode_4
    };

  }

#endif

