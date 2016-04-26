#ifndef __DABDECODE_ENSEMBLE__SERVICE
#define __DABDECODE_ENSEMBLE__SERVICE

#include "ensemble/service_component.h"

#include <cstdint>
#include <set>

namespace dabdecode
  {

  struct service
    {
    service(std::uint32_t const id, bool const isLocal);

    bool operator<(service const & other) const;

    std::uint32_t id() const;

    private:
      void add(service_component && component);

      std::uint32_t const m_id;
      bool const m_isLocal;
      std::set<service_component> m_components{};

      friend struct fic_parser;
    };

  }

#endif

