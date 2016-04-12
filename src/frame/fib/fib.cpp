#include "frame/fib/fib.h"
#include "frame/fib/fig/fig.h"

#include <boost/crc.hpp>

namespace dabdecode
  {

  fib::fib(std::vector<uint8_t> && data)
    : m_data{std::move(data)}
    {
    m_data[30] = ~m_data[30];
    m_data[31] = ~m_data[31];

    if(*this)
      {
      parse_figs();
      }
    }

  fib::operator bool() const
    {
    boost::crc_ccitt_type checker{};
    checker.process_bytes(m_data.data(), 32);

    return !checker.checksum();
    }

  std::vector<fib::fig_pointer> const & fib::figs() const
    {
    return m_figs;
    }

  void fib::parse_figs()
    {
    if(m_data[0] == 255)
      {
      return;
      }

    m_figs.push_back(make_fig({m_data.cbegin(), m_data.cend()}));
    auto processed = m_figs.back()->length() + 1;

    while(processed < 30)
      {
      if(m_data[processed] == 255)
        {
        break;
        }
      else
        {
        m_figs.push_back(make_fig({m_data.cbegin() + processed, m_data.cend()}));
        processed += m_figs.back()->length() + 1;
        }
      }
    }

  }

