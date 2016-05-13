#ifndef __DAB_ENSEMBLE__SERVICE_COMPONENT
#define __DAB_ENSEMBLE__SERVICE_COMPONENT

#include <boost/operators.hpp>

#include <cstdint>
#include <limits>

namespace dab
  {

  namespace __internal_dabdecode
    {
    struct fic_parser;
    }

  /**
   * @brief Transport mechanism descriptors
   *
   * This enum defines the 4 possible transport mechanisms of a service component.
   * Currently only transport_mechanism::package_data is supported.
   */
  enum struct transport_mechanism : std::uint8_t
    {
    stream_audio = 0,
    stream_data = 1,
    fdic = 2,
    package_data = 3
    };

  /**
   * @brief Objects of this class represent Service Components (SCs) as defined in ETSI EN 300 401 Section 6
   *
   * Service Components (SCs) are an important part of DAB. They are what makes up
   * a DAB service. Each component can be associated with multiple Services but can
   * only have one subchannel. Since subchannels are owned by a @ref ensemble, SCs
   * have "references" in the form of id to their associated subchannel.
   */
  struct service_component
    {
    /**
     * @brief Construct a service component
     *
     * A Service component as defined by the ETSI standard (see @ref service_component)
     * is comprised of an id and transport mechanism. It can either be the a primary
     * SC or a secondary. Conditional Access (CA) provides means to "exclude" some users
     * from comsuming a SC by means of encryption for example.
     *
     * @note A value of @p false for the parameter @p caApplies does not necessarily mean
     * that not CA applies to the SC but only that not the whole SC is subject to CA.
     *
     */
    service_component(std::uint16_t const id, transport_mechanism const transport,
                      bool const isPrimary, bool const caApplies);

    /**
     * @brief Get the ID of an SC
     */
    std::uint16_t id() const;

    /**
     * @brief Get the transport mechanism of an SC
     */
    transport_mechanism transport() const;

    /**
     * @brief Check if an SC is a primary SC.
     */
    bool primary() const;

    /**
     * @brief Check if Conditional Access (CA) applies to the full SC.
     */
    bool ca_applies() const;

    /**
     * @brief Get the ID of the associated subchannel
     */
    std::uint8_t subchannel() const;

    /**
     * @brief Get the transported type
     */
    std::uint8_t type() const;

    /**
     * @internal
     *
     * @brief Check if a SC is "less than" another SC.
     *
     * This check only checks whether the id of the current SC is less than the one of
     * @p other.
     *
     * @note ETSI EN 300 401 does not explicitely state that what we consider to be the
     * ID is the actual ID of the SC in all cases. However, Since in the three cases besides
     * MSC packet data the ID is made up in parts of the subchannel ID, it has to be
     * unique in all cases, since all subchannel IDs have to be unique inside an ensemble.
     */
    bool operator<(service_component const & other) const;

    /**
     * @internal
     *
     * @brief Check if two SCs are "equal"
     *
     * This checks only considers SCs with the same ID to be equal. See #operator< for
     * additional notes on the ID of an SC.
     */
    bool operator==(service_component const & other) const;

    private:
      /**
       * @internal
       *
       * @brief Set the associated subchannel id
       */
      void subchannel(std::uint8_t const id);

      /**
       * @internal
       *
       * @brief Set the transported type
       */
      void type(std::uint8_t const type);

      std::uint16_t const m_id;
      transport_mechanism const m_transport;
      bool const m_isPrimary;
      bool const m_caApplies;

      std::uint8_t m_subchannelId{std::numeric_limits<std::uint8_t>::max()};
      std::uint8_t m_type{};

      friend __internal_dabdecode::fic_parser;
    };

  }

#endif

