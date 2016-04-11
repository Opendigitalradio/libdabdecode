#ifndef __DABDECODE_FIGS__FIG0
#define __DABDECODE_FIGS__FIG0

#include "figs/basic_fig.h"

namespace dabdecode
  {

  struct fig0 : basic_fig
    {
    fig0(std::vector<uint8_t> const & data);

    void print(std::ostream & out) const override;

    private:
      std::vector<uint8_t> m_content{};

      bool m_isNext{};
      bool m_isOther{};
      bool m_isData{};

      uint8_t m_extension{};
    };

  std::ostream & operator<<(std::ostream & out, fig0 const & fig);

  }

#endif

