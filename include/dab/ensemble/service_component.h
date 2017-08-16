/*
 * Copyright (C) 2017 Opendigitalradio (http://www.opendigitalradio.org/)
 * Copyright (C) 2017 Felix Morgner <felix.morgner@hsr.ch>
 * Copyright (C) 2017 Tobias Stauber <tobias.stauber@hsr.ch>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DABDECODE_ENSEMBLE_SERVICE_COMPONENT
#define DABDECODE_ENSEMBLE_SERVICE_COMPONENT

#include <cstdint>
#include <limits>
#include <memory>

namespace dab
  {

  namespace internal
    {
    struct fic_parser;
    struct subchannel;
    }

  /**
   * @brief Transport mechanism descriptors
   *
   * This enum defines the 4 possible transport mechanisms of a service component.
   * Currently only transport_mechanism::package_data is supported. An additional
   * mechanism is defined to represent an invalid state.
   */
  enum struct transport_mechanism : std::uint8_t
    {
    stream_audio = 0,
    stream_data = 1,
    fdic = 2,
    package_data = 3,
    unknown = 4
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
     * @brief Get the transported type
     */
    std::uint8_t type() const;

    private:
      /**
       * @internal
       *
       * @brief Service component factory
       *
       * This factory can be used to create a new service component (SC)
       *
       * A Service component as defined by the ETSI standard (see @ref service_component)
       * is comprised of an id and transport mechanism. It can either be the a primary
       * SC or a secondary. Conditional Access (CA) provides means to "exclude" some users
       * from comsuming a SC by means of encryption for example.
       *
       * @note A value of @p false for the parameter @p caApplies does not necessarily mean
       * that not CA applies to the SC but only that not the whole SC is subject to CA.
       */
      static std::shared_ptr<service_component> make(std::uint16_t const id, transport_mechanism const transport,
                                                     bool const isPrimary, bool const caApplies);
      /**
       * @internal
       *
       * @brief Construct a service component
       *
       * @sa #make
       */
      service_component(std::uint16_t const id, transport_mechanism const transport, bool const isPrimary, bool const caApplies);

      /**
       * @internal
       *
       * @brief Get associated subchannel
       */
      std::shared_ptr<internal::subchannel> subchannel() const;

      /**
       * @internal
       *
       * @brief Associate a subchannel with the service component
       */
      void subchannel(std::shared_ptr<internal::subchannel> subchannel);

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

      std::shared_ptr<internal::subchannel> m_subchannel{};
      std::uint8_t m_subchannelId{std::numeric_limits<std::uint8_t>::max()};
      std::uint8_t m_type{};

      friend struct service;
      friend struct ensemble;
      friend internal::fic_parser;
    };

  }

#endif
