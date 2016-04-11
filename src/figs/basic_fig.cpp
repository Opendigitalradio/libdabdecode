#include "figs/basic_fig.h"

#include <iostream>

namespace dabdecode
  {

  basic_fig::basic_fig(std::vector<uint8_t> const & data)
    : m_data{data}
    {

    }

  std::size_t basic_fig::length() const
    {
    return m_data.size();
    }

  void basic_fig::print(std::ostream &) const
    {

    }

  std::ostream & operator<<(std::ostream & out, basic_fig const & fig)
    {
    fig.print(out);
    return out;
    }


  }

