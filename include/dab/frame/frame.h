#ifndef DABDECODE_FRAME_FRAME
#define DABDECODE_FRAME_FRAME

#include "dab/constants/convolution_encoder_attributes.h"
#include "dab/viterbi/fsm.h"

#include <dab/types/transmission_mode.h>

#include <cstdint>
#include <vector>

namespace dab
  {

  namespace internal
    {

    struct frame
      {
      frame(std::vector<float> && data, internal::types::transmission_mode const & mode);

      std::vector<struct fib> fic();

      std::vector<struct cif> msc() const;

      private:
        void extract_fic_codewords();

        std::vector<float> const m_data;
        internal::types::transmission_mode const m_mode;
        fsm const m_fsm;

        std::vector<std::vector<uint8_t>> m_ficCodewords{};
      };

    }

  }

#endif
