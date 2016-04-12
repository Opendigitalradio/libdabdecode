#ifndef __DABDECODE_FRAME_FIB_FIG_FIG_0__FIG_0
#define __DABDECODE_FRAME_FIB_FIG_FIG_0__FIG_0

#include "frame/fib/fig/fig.h"

namespace dabdecode
  {

  struct fig_0 : fig
    {
    fig_0(std::vector<uint8_t> const & data);

    private:
      std::vector<uint8_t> m_content{};

      bool m_isNext{};
      bool m_isOther{};
      bool m_isData{};

      uint8_t m_extension{};
    };

  }

#endif

