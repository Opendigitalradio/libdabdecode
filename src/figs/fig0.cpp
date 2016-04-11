#include "figs/fig0.h"

#include <iostream>

namespace dabdecode
  {

  fig0::fig0(std::vector<uint8_t> const & data)
    : basic_fig(data)
    {
    m_isNext  = m_data[0] >> 7 & 1;
    m_isOther = m_data[0] >> 6 & 1;
    m_isData  = m_data[0] >> 5 & 1;

    m_extension = m_data[0] & 31;
    }

  void fig0::print(std::ostream & out) const
    {
    out << "FIG/0 C/N: " << m_isNext
        << " OE: " << m_isOther
        << " P/D: " << m_isData
        << " EXT: " << m_extension
        << '\n';
    }

  std::ostream & operator<<(std::ostream & out, fig0 const & fig)
    {
    fig.print(out);
    return out;
    }

  }

