#ifndef __DABDECODE_MODES__BASIC_MODE
#define __DABDECODE_MODES__BASIC_MODE

#include <type_traits>

namespace dabdecode
  {

  template<std::size_t Carriers,
           std::size_t FrameSymbols,
           std::size_t FicSymbols,
           std::size_t FrameFibs,
           std::size_t FrameCifs>
  struct basic_mode
    {
    /*
     * @internal
     *
     * The number of carriers for the selected transport mode.
     */
    using carriers = std::integral_constant<std::size_t, Carriers>;

    /*
     * @internal
     *
     * The number of symbols that make up a single frame.
     */
    using frame_symbols = std::integral_constant<std::size_t, FrameSymbols>;

    /*
     * @internal
     *
     * The number of symbols that make up the Fast Information Channel (FIC).
     */
    using fic_symbols = std::integral_constant<std::size_t, FicSymbols>;

    /*
     * @internal
     *
     * The number of symbols that kame up the Main Service Channel (MSC).
     */
    using msc_symbols = std::integral_constant<std::size_t, FrameSymbols - FicSymbols>;

    /*
     * @internal
     *
     * The number of Fast Information Blocks (FIBs) in a single frame.
     */
    using frame_fibs = std::integral_constant<std::size_t, FrameFibs>;

    /*
     * @internal
     *
     * The number of Common Interleaved Frames (CIFs) contained in a single frame.
     */
    using frame_cifs = std::integral_constant<std::size_t, FrameCifs>;

    /*
     * @internal
     *
     * The number of bits the make up a FIB codeword. Each codeword contains a group of FIBs that describe a CIF.
     */
    using fib_codeword_bits = std::integral_constant<std::size_t, frame_fibs::value * 256 / frame_cifs::value>;

    /*
     * @internal
     *
     * The number of bits in a symbol.
     */
    using symbol_bits = std::integral_constant<std::size_t, carriers::value * 2>;
    };

  }

#endif

