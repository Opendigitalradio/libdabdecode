#ifndef __DABDECODE_CONSTANTS__TRANSMISSION_MODE
#define __DABDECODE_CONSTANTS__TRANSMISSION_MODE

#include <cstdint>

namespace dabdecode
  {

  namespace constants
    {

    /**
     * @brief DAB transmission mode enumeration
     *
     * This enum declares the currently standardized transmission modes.
     * The dabdecode::ensemble class uses these modes to determine how to decode
     * the received frames. You can speficy the mode of a ensemble in
     * its constructor. You will need to know what transmission mode is used in
     * the DAB ensemble you are trying to receive.
     *
     * @internal
     * The modes that are declared here are specified in ETSI EN 300 401
     * @endinternal
     *
     * @see dabdecode::ensemble
     */
    enum struct transmission_mode : uint8_t
      {
      mode_1,
      mode_2,
      mode_3,
      mode_4
      };

    }

  }

#endif

