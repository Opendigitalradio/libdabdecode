#ifndef __DABDECODE_FRAME_FIB_FIG_FIG_1__FIG_1
#define __DABDECODE_FRAME_FIB_FIG_FIG_1__FIG_1

#include "frame/fib/fig/extension.h"
#include "frame/fib/fig/fig.h"

namespace dabdecode
  {

  struct fig_1 : fig
    {

    struct extension_0 : extension
      {
      extension_0(uint16_t const id);
      uint16_t const ensembleId;
      };

    struct extension_1 : extension
      {
      extension_1(uint16_t const id);
      uint16_t const serviceId;
      };

    struct extension_5 : extension
      {
      extension_5(uint32_t const id);
      uint32_t const serviceId;
      };

    fig_1(std::vector<uint8_t> const & data);

    explicit operator std::string() const;

    private:
      void parse_extension();
      void parse_label();
      std::string m_label;
    };

  }

#endif

