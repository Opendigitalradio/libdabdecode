#ifndef __DABDECODE_ENSEMBLE__SERVICE_COMPONENT
#define __DABDECODE_ENSEMBLE__SERVICE_COMPONENT

#include <cstdint>

namespace dabdecode
  {

  enum struct transport_mechanism : std::uint8_t
    {
    stream_audio = 0,
    stream_data = 1,
    fdic = 2,
    package_data = 3
    };

  struct service_component
    {
    std::uint16_t const id;
    transport_mechanism const transport;
    bool const isPrimary;
    bool const caApplies;

    bool operator<(service_component const & other) const;
    };

  }

#endif

