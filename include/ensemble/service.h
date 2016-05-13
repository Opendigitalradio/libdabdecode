#ifndef __DAB_ENSEMBLE__SERVICE
#define __DAB_ENSEMBLE__SERVICE

#include "ensemble/service_component.h"

#include <boost/operators.hpp>

#include <cstdint>
#include <set>
#include <string>

namespace dab
  {

  /**
   * @brief The types of different services.
   *
   * This enum declares the two different types of service currently
   * specified in DAB.
   *
   * @sa service::type
   */
  enum struct service_type : std::uint8_t
    {
    programme,
    data
    };

  struct ensemble;

  namespace __internal_dabdecode
    {
    struct fic_parser;
    }

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
    service_type type() const;

    private:
      service(std::uint32_t const id, bool const isLocal);

      void add(service_component const & component);

      void label(std::string && label);

      void type(service_type const type);

      std::uint16_t primary() const;

      void primary(std::uint16_t const component);

      std::uint32_t const m_id;
      bool const m_isLocal;

      std::string m_label{};
      service_type m_type{service_type::programme};

      std::uint16_t m_primaryComponent{};
      std::set<std::uint16_t> m_components{};

      friend __internal_dabdecode::fic_parser;
      friend ensemble;
    };

  }

#endif

