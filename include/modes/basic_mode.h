#ifndef __DABDECODE_MODES__BASIC_MODE
#define __DABDECODE_MODES__BASIC_MODE

#include <type_traits>

namespace dabdecode
  {

  template<std::size_t Carriers,
           std::size_t SymbolsPerFrame,
           std::size_t SymbolsPerFic,
           std::size_t CodewordsPerFic,
           std::size_t FibsPerCodeword,
           std::size_t UnpuncturedCodewordLength,
           std::size_t DeconvolvedCodewordLength>
  struct basic_mode
    {
    using carriers = std::integral_constant<std::size_t, Carriers>;
    auto static constexpr carriers_v = carriers::value;

    using symbols_per_frame = std::integral_constant<std::size_t, SymbolsPerFrame>;
    auto static constexpr symbols_per_frame_v = symbols_per_frame::value;

    using symbols_per_fic = std::integral_constant<std::size_t, SymbolsPerFic>;
    auto static constexpr symbols_per_fic_v = symbols_per_fic::value;

    using codewords_per_fic = std::integral_constant<std::size_t, CodewordsPerFic>;
    auto static constexpr codewords_per_fic_v = codewords_per_fic::value;

    using fibs_per_codeword = std::integral_constant<std::size_t, FibsPerCodeword>;
    auto static constexpr fibs_per_codeword_v = fibs_per_codeword::value;

    using unpunctured_codeword_length = std::integral_constant<std::size_t, UnpuncturedCodewordLength>;
    auto static constexpr unpunctured_codeword_length_v = unpunctured_codeword_length::value;

    using deconvolved_codeword_length = std::integral_constant<std::size_t, DeconvolvedCodewordLength>;
    auto static constexpr deconvolved_codeword_length_v = deconvolved_codeword_length::value;
    };

  }

#endif

