#include "frame/fib.h"

#include <boost/crc.hpp>

namespace dab
  {

  namespace __internal_dabdecode
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

      while(it != m_end)
        {
        checker.process_byte(*it);
        ++it;
        }

      return !checker.checksum();
      }

    fib::iterator fib::begin() const
      {
      return m_begin;
      }

    fib::iterator fib::end() const
      {
      return m_end - 2;
      }

    }

  }

