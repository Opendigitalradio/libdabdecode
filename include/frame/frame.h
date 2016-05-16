#ifndef __DAB__FRAME
#define __DAB__FRAME

#include "constants/convolution_encoder_attributes.h"
#include "viterbi/fsm.h"

#include <types/transmission_mode.h>

#include <cstdint>
#include <vector>

namespace dab
  {

  namespace __internal_dabdecode
    {

    struct frame
      {
      frame(std::vector<float> && data, __internal_common::types::transmission_mode const & mode);

      std::vector<struct fib> fic();

      std::vector<struct cif> msc() const;

      private:
        void extract_fic_codewords();

        std::vector<float> const m_data;
        __internal_common::types::transmission_mode const m_mode;
        fsm const m_fsm;

        std::vector<std::vector<uint8_t>> m_ficCodewords{};
      };

    }

  }

#endif

