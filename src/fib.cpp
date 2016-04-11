#include "fib.h"

#include <boost/crc.hpp>

namespace dabdecode
  {

  fib::fib(std::vector<uint8_t> && data)
    : m_data{std::move(data)}
    {
    m_data[30] = ~m_data[30];
    m_data[31] = ~m_data[31];
    }

  fib::operator bool() const
    {
    boost::crc_ccitt_type checker{};
    checker.process_bytes(m_data.data(), 32);

    return !checker.checksum();
    }

  }

