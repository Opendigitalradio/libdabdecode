#include "frame/fib/fig/fig_0/fig_0.h"
#include "ensemble/ensemble.h"

#include <iostream>

namespace dabdecode
  {

  fig_0::fig_0(std::vector<uint8_t> const & data)
    : fig(data)
    {
    m_isNext  = m_dataField[0] >> 7 & 1;
    m_isOther = m_dataField[0] >> 6 & 1;
    m_isData  = m_dataField[0] >> 5 & 1;

    parse_extension();
    }

  void fig_0::dispatch(ensemble & target) const
    {
    target.handle(*this);
    }

  void fig_0::parse_extension()
    {
    switch(m_dataField[0] & 63)
      {
      case 0:
        m_extension = new extension_0{{m_dataField.begin() + 1, m_dataField.end()}};
        break;
      case 1:
        m_extension = new extension_1{{m_dataField.begin() + 1, m_dataField.end()}};
        break;
      default:
        break;
      }
    }

  }

