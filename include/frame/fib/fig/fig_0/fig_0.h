#ifndef __DABDECODE_FRAME_FIB_FIG_FIG_0__FIG_0
#define __DABDECODE_FRAME_FIB_FIG_FIG_0__FIG_0

#include "frame/fib/fig/extension.h"
#include "frame/fib/fig/fig.h"

#include <array>
#include <cstdint>

namespace dabdecode
  {

  struct fig_0 : fig
    {

    struct extension_0 : extension
      {
      extension_0(std::vector<uint8_t> const & data);

      uint8_t type() const override;

      uint8_t const countryId;
      uint16_t const ensembleId;
      uint8_t const change;
      bool const hasAlarm;
      uint8_t const cifCountHigh;
      uint8_t const cifCountLow;
      uint8_t const occcurenceChange;
      };

    fig_0(std::vector<uint8_t> const & data);

    virtual void dispatch(ensemble & target) const override;

    private:
      void parse_extension();

      std::vector<uint8_t> m_content{};

      bool m_isNext{};
      bool m_isOther{};
      bool m_isData{};
    };

  }

#endif

