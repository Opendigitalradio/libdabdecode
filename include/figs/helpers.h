#ifndef __DEBDECODE_FIGS__HELPERS
#define __DEBDECODE_FIGS__HELPERS

#include <cstdint>
#include <memory>
#include <vector>

namespace dabdecode
  {

  std::shared_ptr<struct basic_fig> make_fig(std::vector<uint8_t> const & data);

  }


#endif

