#ifndef __DABDECODE__FRAME
#define __DABDECODE__FRAME

#include <cstdint>
#include <vector>

#include "constants/convolution_encoder_attributes.h"
#include "fib/fib.h"
#include "viterbi/fsm.h"


namespace dabdecode
  {

  struct frame
    {
    frame(std::vector<float> && data, std::size_t const mode);

    std::vector<fib> fic();

    private:
      void extract_fic_codewords();

      fsm const m_fsm{constants::kEncoderInputLength,
                      constants::kEncoderOutputLength,
                      {constants::kEncoderPolynomials.cbegin(), constants::kEncoderPolynomials.cend()}};

      std::vector<float> const m_data;
      std::size_t const m_mode;

      std::vector<std::vector<uint8_t>> m_ficCodewords{};
    };

  }

#endif
