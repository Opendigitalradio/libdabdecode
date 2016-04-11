#ifndef __DABDECODE__FIB
#define __DABDECODE__FIB

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <vector>

namespace dabdecode
  {

  struct basic_fig;

  struct fib
    {
    fib(std::vector<uint8_t> && data);

    operator bool() const;

    std::vector<std::shared_ptr<basic_fig>> const & figs() const;

    private:
      void parse_figs();

      std::vector<uint8_t> m_data;
      std::vector<std::shared_ptr<basic_fig>> m_figs{};

      friend std::ostream & operator<<(std::ostream &, fib const &);
    };

  std::ostream & operator<<(std::ostream & out, fib const & fib);

  }

#endif
