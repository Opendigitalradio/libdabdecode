#include "figs/basic_fig.h"
#include "figs/fig0.h"
#include "figs/helpers.h"

namespace dabdecode
  {

  std::shared_ptr<basic_fig> make_fig(std::vector<uint8_t> const & data)
    {
    auto type = (data[0] >> 5) & 7;
    auto length = data[0] & 31;

    auto beginIterator = data.cbegin() + 1;
    auto endIterator = beginIterator + length;

    switch(type)
      {
      case 0:
        return std::make_shared<fig0>(std::vector<uint8_t>{beginIterator, endIterator});
      default:
        return std::make_shared<basic_fig>(std::vector<uint8_t>{beginIterator, endIterator});
      }
    }

  }
