#include "fib.h"
#include "figs/helpers.h"
#include "figs/basic_fig.h"

#include <boost/crc.hpp>

#include <iostream>

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

  std::vector<std::shared_ptr<basic_fig>> const & fib::figs() const
    {
    return m_figs;
    }

  void fib::parse_figs()
    {
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

  std::ostream & operator<<(std::ostream & out, fib const & fib)
    {
    for(auto & byte : fib.m_data)
      {
      std::cout << byte;
      }

    return out;
    }

  }

