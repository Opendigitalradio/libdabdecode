#ifndef __DABDECODE__FRAME
#define __DABDECODE__FRAME

#include <cstdint>
#include <vector>

#include "constants/convolution_encoder_attributes.h"
#include "viterbi/fsm.h"
#include "constants/transmission_mode.h"

namespace dabdecode
  {

  struct frame
    {
    frame(std::vector<float> && data, constants::transmission_mode const mode);

    std::vector<struct fib> fic();

    std::vector<struct cif> msc() const;

    private:
      void extract_fic_codewords();

      fsm const m_fsm{constants::kEncoderInputLength,
                      constants::kEncoderOutputLength,
                      {constants::kEncoderPolynomials.cbegin(), constants::kEncoderPolynomials.cend()}};

      std::vector<float> const m_data;
      constants::transmission_mode const m_mode;

      std::vector<std::vector<uint8_t>> m_ficCodewords{};
    };

  }

#endif

