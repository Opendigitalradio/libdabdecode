#include "frame/fib.h"

#include <boost/crc.hpp>

namespace dabdecode
  {

  fib::fib(fib::iterator const & begin, fib::iterator const & end)
    : m_begin{begin},
      m_end{end}
    {

    }

  fib::operator bool() const
    {
    boost::crc_ccitt_type checker{};
    auto it = m_begin;

    while(it != m_begin + 30)
      {
      checker.process_byte(*it++);
      }

    while(it != m_end)
      {
      checker.process_byte(~*it++);
      }

    return !checker.checksum();
    }

  fib::iterator fib::begin()
    {
    return m_begin;
    }

  fib::iterator fib::end()
    {
    return m_end;
    }

  }

