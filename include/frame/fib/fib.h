#ifndef __DABDECODE_FRAME_FIB__FIB
#define __DABDECODE_FRAME_FIB__FIB

#include "frame/fib/fig/fig.h"

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <vector>

namespace dabdecode
  {

  struct fib
    {
    using fig_pointer = std::shared_ptr<fig>;

    fib(std::vector<uint8_t> && data);

    operator bool() const;

    std::vector<fig_pointer> const & figs() const;

    private:
      void parse_figs();

      std::vector<uint8_t> m_data;
      std::vector<fig_pointer> m_figs{};
    };

  }

#endif
