#include "frame/cif.h"

namespace dabdecode
  {

  cif::cif(cif::iterator const & begin, cif::iterator const & end)
    : m_begin{begin},
      m_end{end}
    {

    }

  cif::iterator cif::begin() const
    {
    return m_begin;
    }

  cif::iterator cif::end() const
    {
    return m_end;
    }

  }
