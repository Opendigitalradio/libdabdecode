#include "frame/fib/fig/fig_1/fig_1.h"

namespace dabdecode
  {

  fig_1::fig_1(std::vector<uint8_t> const & data)
    : fig{data}
    {
    parse_extension();
    parse_label();
    }

  fig_1::operator std::string() const
    {
    return m_label;
    }

  void fig_1::parse_extension()
    {
    switch(m_dataField[0] & 3)
      {
      case 0:
        m_extension = std::make_shared<extension_0>(uint16_t((((uint16_t) m_dataField[1]) << 8) | m_dataField[2]));
        break;
      default:
        break;
      }
    }

  void fig_1::parse_label()
    {
    if(m_extension)
      {
      auto offset = 1 + m_extension->length();
      m_label = std::string{m_dataField.cbegin() + offset, m_dataField.cbegin() + offset + 16};
      }
    }

  }

