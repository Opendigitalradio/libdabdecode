#ifndef __DABDECODE_CONSTANTS__SERVICE_TYPES
#define __DABDECODE_CONSTANTS__SERVICE_TYPES

#include <cstdint>

namespace dabdecode
  {

  namespace constants
    {

    /**
     * @brief The types of different services.
     *
     * This enum declares the two different types of service currently
     * specified in DAB.
     *
     * @sa service::type
     */
    enum struct service_type : std::uint8_t
      {
      programme,
      data
      };

    }

  }

#endif

