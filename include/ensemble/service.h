#ifndef __DAB_ENSEMBLE__SERVICE
#define __DAB_ENSEMBLE__SERVICE

#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace dab
  {

  struct service_component;
  struct ensemble;

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
  struct service
    {
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

    /**
     * @brief Retrieve the service label
     */
    std::string const & label() const;

    /**
     * @brief Retrieve the primary service component of a service
     */
    std::shared_ptr<service_component> primary() const;

    private:
      static std::shared_ptr<service> make(std::uint32_t const id, bool const isLocal);

      service(std::uint32_t const id, bool const isLocal);

      void add(std::shared_ptr<service_component> component);

      void label(std::string && label);

      void type(service_type const type);

      void primary(std::shared_ptr<service_component> component);

      std::uint32_t const m_id;
      bool const m_isLocal;

      std::string m_label{};
      service_type m_type{service_type::programme};

      std::shared_ptr<service_component> m_primaryComponent{};
      std::map<std::uint16_t, std::shared_ptr<service_component>> m_components{};

      friend __internal_dabdecode::fic_parser;
      friend ensemble;
    };

  }

#endif

