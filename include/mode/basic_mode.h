#ifndef __DABDECODE_MODES__BASIC_MODE
#define __DABDECODE_MODES__BASIC_MODE

#include <type_traits>

/**
 * @internal
 * @file
 * @author Felix Morgner
 *
 * @brief This file contains the definition of the template base for DAB transmission modes
 */

namespace dabdecode
  {

  /**
   * @internal
   * @brief This class is the a template base for the different DAB modes
   *
   * @tparam Carriers The number of OFDM subcarriers for the transfer mode
   * @tparam FrameSymbols The number of OFDM symbols, including the PR, for each frame
   * @tparam FicSymbols The number of OFDM symbols that make up the FIC
   * @tparam FrameFibs The number of FIBs per frame for the transfer mode
   * @tparam FrameCifs The number of CIFs that make up the MSC of the frame
   *
   * This class provides a number of type members that contain compile-time constant
   * information related to the different modes supported by DAB. There exist some
   * specializations in the file modes.h that represent the 4 currently standardized
   * DAB transfer modes.
   *
   * @note This class is not thought to be used for instanciating object. Even though it
   * would be possible, functions would require to be templated. We therefore encourage the
   * use of values of type dabdecode::transmission_mode_t to specify modes. There exists a
   * couple of * free functions to retrieve mode related information via
   * dabdecode::transmission_mode_t values. We chose this design as it allows clean
   * compiletime computation without a large amount of cryptic nested if/elses.
   */
  template<std::size_t Carriers,
           std::size_t FrameSymbols,
           std::size_t FicSymbols,
           std::size_t FrameFibs,
           std::size_t FrameCifs>
  struct basic_mode
    {
    /**
     * @internal
     *
     * @brief The number of carriers for the selected transport mode.
     *
     * Each transport mode is associated with a different number of OFDM subcarriers. The
     * @p value member of this type provides access to the number of OFDM subcarriers.
     */
    using carriers = std::integral_constant<std::size_t, Carriers>;

    /**
     * @internal
     *
     * @brief The number of symbols that make up a single frame.
     *
     * Each DAB transport frame is made up of a certain number of OFDM symbols. This type alias
     * provides a member called @p value that allows access to the number of symbols per frame.
     *
     * @note This typedef reduces the actual supplied number by 1, since we strip away the
     * phase-reference symbol.
     */
    using frame_symbols = std::integral_constant<std::size_t, FrameSymbols - 1>;

    /**
     * @internal
     *
     * @brief The number of symbols that make up the Fast Information Channel (FIC).
     *
     * The Fast Information Channel (FIC) is made up of a certain number of symbols, depending
     * on the transfer mode. The FIC carries information describing the DAB ensemble that is
     * being broadcast on a specific frequency.
     */
    using fic_symbols = std::integral_constant<std::size_t, FicSymbols>;

    /**
     * @internal
     *
     * @brief The number of symbols that make up the Main Service Channel (MSC).
     *
     * The number of symbols making up the Main Service Channel (MSC) is dependent upon the
     * transfer mode. The number of MSC symbols is calculated directly from the value carried in
     * frame_symbols and fic_symbols.
     */
    using msc_symbols = std::integral_constant<std::size_t, frame_symbols::value - FicSymbols>;

    /**
     * @internal
     *
     * @brief The number of Fast Information Blocks (FIBs) in a single frame.
     *
     * Each DAB transfer mode use a different number of Fast Information Blocks. These blocks
     * carry the so called Fast Information Groups, which in turn carry the actual information
     * describing the structure of the DAB ensemble.
     */
    using frame_fibs = std::integral_constant<std::size_t, FrameFibs>;

    /**
     * @internal
     *
     * @brief The number of Common Interleaved Frames (CIFs) contained in a single frame.
     *
     * A DAB frame, or rather the MSC of a DAB frame, is made up of a mode dependent number of
     * Common Interleaved Frames (CIFs). These CIFs contain the so-called Capacity Units (CUs)
     * which in turn carry the services of an ensemble.
     */
    using frame_cifs = std::integral_constant<std::size_t, FrameCifs>;

    /**
     * @internal
     *
     * @brief The number of bits that make up a FIB codeword.
     *
     * The FIBs are made up of convolutionally coded codewords. Each group of codewords makes
     * up a FIB and describes a single CIF. The number of FIB bits is equal to the number of
     * FIBs times 256 bit per byte devided by the number of cifs.
     */
    using fib_codeword_bits = std::integral_constant<std::size_t, frame_fibs::value * 256 / frame_cifs::value>;

    /**
     * @internal
     *
     * @brief The number of bits in a symbol.
     *
     * Each OFDM symbol in DAB transports 2 bits of information due to the QPSK used in DAB.
     */
    using symbol_bits = std::integral_constant<std::size_t, carriers::value * 2>;
    };

  }

#endif

