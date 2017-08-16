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

#ifndef DABDECODE_ENSEMBLE_SERVICE
#define DABDECODE_ENSEMBLE_SERVICE

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

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

  namespace internal
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

      void set_handler(std::function<void (std::vector<std::uint8_t>)> handler);

      std::uint32_t const m_id;
      bool const m_isLocal;

      std::string m_label{};
      service_type m_type{service_type::programme};

      std::shared_ptr<service_component> m_primaryComponent{};
      std::map<std::uint16_t, std::shared_ptr<service_component>> m_components{};

      friend internal::fic_parser;
      friend ensemble;
    };

  }

#endif
