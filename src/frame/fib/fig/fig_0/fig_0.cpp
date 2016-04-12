#include "frame/fib/fig/fig_0/fig_0.h"

namespace dabdecode
  {

  fig_0::fig_0(std::vector<uint8_t> const & data)
    : fig(data)
    {
    m_isNext  = m_dataField[0] >> 7 & 1;
    m_isOther = m_dataField[0] >> 6 & 1;
    m_isData  = m_dataField[0] >> 5 & 1;

    m_extension = m_dataField[0] & 31;
    }

  }

