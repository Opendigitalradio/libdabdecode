#include "ensemble/subchannel.h"

namespace dabdecode
  {

  bool subchannel::operator<(subchannel const & other) const
    {
    return id < other.id;
    }

  }

