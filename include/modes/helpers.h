#ifndef __DABDECODE_MODES__HELPERS
#define __DABDECODE_MODES__HELPERS

#include <cstdint>

namespace dabdecode
  {

  std::size_t frame_size(std::size_t const mode);

  std::size_t fic_size(std::size_t const mode);

  std::size_t punctured_codeword_size(std::size_t const mode);

  std::size_t fic_codeword_size(std::size_t const mode);

  std::size_t fibs_in_codeword(std::size_t const mode);

  }

#endif

