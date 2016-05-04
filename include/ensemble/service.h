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

  /**
   * @brief Object of this type represent DAB services (like radio stations)
   *
   * A service in DAB is somewhat comaparable to classic AM/FM radio stations.
   * Most services transport audio with some associated data like traffic alerts,
   * album covers, etc. Thus the service, besides the @ref ensemble is what
   * you will want to use to received audio/data transmitted via DAB.
   */
  struct service : boost::less_than_comparable<service>, boost::equality_comparable<service>
    {

    bool operator<(service const & other) const;

    bool operator==(service const & other) const;

    /**
     * @brief Retrive the ID of a service
     *
     * The ID of a service uniquely identifies it inside an ensemble. Thus, the ID
     * can be used as an index in lists, sets, etc.
     */
    std::uint32_t id() const;

    /**
     * @brief Get the type of a service
     *
     * DAB services come in two main fashions. The first one is a so-called programme
     * service. A programme service transports audio as its primary functionality,
     * comparable to classic AM/FM radio. The second type of services are data services.
     * A data service transports mainly data, thus the name, like multimedia object or
     * IP datagrams.
     *
     * @see service_type
     */
    constants::service_type type() const;

    private:
      service(std::uint32_t const id, bool const isLocal);

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

