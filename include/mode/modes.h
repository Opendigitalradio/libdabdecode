#ifndef __DABDECODE_MODE__MODES
#define __DABDECODE_MODE__MODES

#include "mode/basic_mode.h"

namespace dabdecode
  {

  using mode_1 = basic_mode<1536,  75, 3, 12, 4>;
  using mode_2 = basic_mode< 384,  75, 3,  3, 1>;
  using mode_3 = basic_mode< 192, 152, 8,  4, 1>;
  using mode_4 = basic_mode< 768,  75, 3,  6, 2>;

  std::size_t frame_size(std::size_t const mode);

  std::size_t fic_size(std::size_t const mode);

  std::size_t punctured_codeword_size(std::size_t const mode);

  std::size_t fic_codeword_size(std::size_t const mode);

  std::size_t fibs_in_codeword(std::size_t const mode);

  }

#endif

