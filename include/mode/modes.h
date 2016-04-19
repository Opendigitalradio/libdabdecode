#ifndef __DABDECODE_MODE__MODES
#define __DABDECODE_MODE__MODES

#include "mode/basic_mode.h"
#include "mode/transport_mode.h"

/**
 * @internal
 * @file
 * @author Felix Morgner
 *
 * @defgroup dab_modes DAB Transfer modes
 * @brief This file contains the definitions of the 4 standardized DAB transport modes.
 *
 * The DAB standard currently defines 4 transport modes. Each of these transport modes is
 * used in specific scenarios and on the different frequency bands. For more information
 * on the modes and their uses, refer to ETSI EN 300 401 or "Digital Audio Broadcasting -
 * Priciples and Applications of DAB, DAB+ and DMB" by Wolfgang Hoeg and Thomas Lauterbach.
 *
 * In addition to the instantiations of dabdecode::basic_mode, this file also declares some
 * convenience functions to get transform the user supplied values of
 * dabdecode::transport_mode.
 */

namespace dabdecode
  {

  namespace constants
    {

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 1 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 1. See
     * dabdecode::basic_mode for more information.
     */
    using mode_1 = basic_mode<1536,  76, 3, 12, 4>;

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 2 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 2. See
     * dabdecode::basic_mode for more information.
     */
    using mode_2 = basic_mode< 384,  76, 3,  3, 1>;

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 3 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 3. See
     * dabdecode::basic_mode for more information.
     */
    using mode_3 = basic_mode< 192, 153, 8,  4, 1>;

    /**
     * @ingroup dab_modes
     * @brief DAB transport mode 4 descriptor
     *
     * This type alias generates the descriptor for DAB transport mode 4. See
     * dabdecode::basic_mode for more information.
     */
    using mode_4 = basic_mode< 768,  76, 3,  6, 2>;

    }

  std::size_t frame_size(transport_mode const mode) noexcept;

  std::size_t fic_size(transport_mode const mode) noexcept;

  std::size_t punctured_codeword_size(transport_mode const mode) noexcept;

  std::size_t fic_codeword_size(transport_mode const mode) noexcept;

  std::size_t fibs_in_codeword(transport_mode const mode) noexcept;

  std::size_t frame_symbols(transport_mode const mode) noexcept;

  std::size_t symbol_size(transport_mode const mode) noexcept;

  }

#endif

