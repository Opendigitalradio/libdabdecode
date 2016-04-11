#ifndef __DABDECODE__FIB
#define __DABDECODE__FIB

#include <cstdint>
#include <vector>

namespace dabdecode
  {

  struct fib
    {
    fib(std::vector<uint8_t> && data);

    operator bool() const;

    private:
      std::vector<uint8_t> m_data;
    };

  }

#endif
