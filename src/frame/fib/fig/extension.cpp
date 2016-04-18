#include "frame/fib/fig/extension.h"

namespace dabdecode
  {

  extension::extension(std::vector<uint8_t> const & data)
    : m_dataField{data}
    {

    }

  std::size_t extension::length() const
    {
    return m_dataField.size();
    }

  }

