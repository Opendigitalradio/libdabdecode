#include "ensemble/service_component.h"

namespace dabdecode
  {

  bool service_component::operator<(service_component const & other) const
    {
    return id < other.id;
    }

  }

