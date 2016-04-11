#ifndef __DABDECODE_FIGS__BASIC_FIG
#define __DABDECODE_FIGS__BASIC_FIG

#include <cstdint>
#include <iosfwd>
#include <vector>

namespace dabdecode
  {

  struct basic_fig
    {
    basic_fig(std::vector<uint8_t> const & data);

    virtual ~basic_fig() = default;

    std::size_t length() const;

    virtual void print(std::ostream & out) const;

    protected:
      std::vector<uint8_t> const m_data;
    };

  std::ostream & operator<<(std::ostream &, basic_fig const &);

  }

#endif

