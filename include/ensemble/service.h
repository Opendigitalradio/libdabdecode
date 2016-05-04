#ifndef __DABDECODE_ENSEMBLE__SERVICE
#define __DABDECODE_ENSEMBLE__SERVICE

#include "constants/service_types.h"
#include "ensemble/service_component.h"

#include <boost/operators.hpp>

#include <cstdint>
#include <set>
#include <string>

namespace dabdecode
  {

  struct service : boost::less_than_comparable<service>, boost::equality_comparable<service>
    {
    service(std::uint32_t const id, bool const isLocal);

    bool operator<(service const & other) const;
    bool operator==(service const & other) const;

    std::uint32_t id() const;

    private:
      void add(service_component const & component);

      void label(std::string && label);

      void type(constants::service_type const type);

      std::uint32_t const m_id;
      bool const m_isLocal;

      std::string m_label{};
      constants::service_type m_type{constants::service_type::programme};

      std::set<std::uint16_t> m_components{};

      friend struct fic_parser;
    };

  }

#endif

