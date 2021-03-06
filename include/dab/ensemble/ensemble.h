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

#ifndef DABDECODE_ENSEMBLE_ENSEMBLE
#define DABDECODE_ENSEMBLE_ENSEMBLE

#include "dab/ensemble/subchannel.h"
#include "dab/ensemble/service.h"

#include "dab/frame/frame.h"

#include "dab/parser/fic_parser.h"

#include <dab/constants/transmission_modes.h>
#include <dab/types/common_types.h>

#include <atomic>
#include <cstdint>
#include <chrono>
#include <functional>
#include <iosfwd>
#include <string>
#include <memory>
#include <set>
#include <map>

namespace dab
  {

  struct service_component;
  enum struct transport_mechanism : std::uint8_t;

  /**
   * @brief Access information and data of a DAB ensemble
   *
   * This class provides acces to the information and data of a
   * DAB ensemble. It gives access to services and subchannels.
   */

  struct ensemble
    {
    /**
     * @brief Construct a @ref ensemble that acquires samples from the specified queue
     *
     * An ensemble is the most basic and interesting entity exposed by libdabdecode.
     * It provides access to data services and audio services, also called programmes.
     * The transmission mode can be specified vi the @p mode argument, with possible
     * values being @p kTransmissionMode1, @p kTransmissionMode2, @p kTransmissionMode3
     * and @p kTransmissionMode4 in the namespace @p dab::transmission_modes
     *
     * @param symbols The OFDM symbol queue
     * @param mode The transmission mode used for the ensemble
     */
    ensemble(symbol_queue_t & symbols, internal::types::transmission_mode const & mode);

    /**
     * @brief Retrieve the label of the ensemble
     *
     * Each ensemble carries a, not necessarily unique, label. Calling this function
     * retrieves the full lable as advertised in the respective FIGs. DAB also has the
     * concept of short labels, that are at most 8 bytes long. Please note that this
     * function always returns the FULL label, not the shortened one.
     */
    std::string const & label() const;

    /**
     * @brief Retrieve the ensembles id
     *
     * An ensemble has a unique identifier, the so-called EnsembleId. This identifier
     * consits of two parts, the first being a 4-bit country identifier while the second
     * one is a 16-bit identifier that must be unique within one countries ensembles.
     * This function returns the complete identifier. To access country id, use
     * #country and to retrieve the national ensemble reference you can use #reference.
     */
    std::uint16_t id() const;

    /**
     * @brief Retrieve the ensembles country id
     *
     * @see #id
     */
    std::uint8_t country() const;

    /**
     * @brief Retrieve the ensembles national reference
     *
     * @see #id
     */
    std::uint16_t reference() const;

    /**
     * @brief Access the list of services present in the ensemble
     *
     * This function returns the set of services that are present within
     * the ensemble. Services might come and go during the lifetime of
     * an ensemble. To activate the decoding of a service, you need to
     * select a service from this set and pass it to the #activate function.
     */
    std::map<std::uint32_t, std::shared_ptr<service>> const & services() const;

    /**
     * @brief Update the ensemble
     *
     * This function updates an ensemble from the datastream supplied during
     * construction. This includes updating the currently active service.
     */
    bool update();

    /**
     * @brief Abort the current update
     */
    void abort();

    /**
     * @brief Activate a service for decoding
     *
     * This function activates a service for decoding. The reference to the
     * service might be obtained via the function #services.
     *
     * @see #services
     */
    void activate(std::shared_ptr<service> const & service, std::function<void (std::vector<std::uint8_t>)> handler);

    /**
     * @brief Check if the ensemble is valid
     *
     * This function return true iff the ensemble is in a valid state. If the ensemble
     * is in a valid state, the list ob #services and the #label, #reference and #country
     * may be accessed safely.
     */
    explicit operator bool() const;

    private:
      /**
       * @internal
       *
       * @brief Extract the next frame
       *
       * This function is used to extract the next frame from the input data stream.
       * It assembles the whole frame and stores it in m_frame.
       *
       * @return true if extraction was successful, false otherwise
       */
      bool next_frame();

      /**
       * @internal
       *
       * @brief Set the ensemble label
       */
      void label(std::string const & label);

      /**
       * @internal
       *
       * @brief Set the ensemble id
       */
      void id(std::uint16_t const id);

      /**
       * @internal
       *
       * @brief Add a subchannel to the ensemble
       */
      void add(std::shared_ptr<internal::subchannel> subchannel);

      /**
       * @internal
       *
       * @brief Add a service to the ensemble
       */
      void add(std::shared_ptr<service> service);

      /**
       * @internal
       *
       * @brief Add a service component to the ensemble
       */
      void add(std::shared_ptr<service_component> component);

      symbol_queue_t & m_symbolQueue;
      internal::types::transmission_mode const & m_mode;

      internal::fic_parser m_ficParser{*this};
      std::unique_ptr<internal::frame> m_frame{};

      std::map<std::uint32_t, std::shared_ptr<service>> m_services{};
      std::map<std::uint16_t, std::shared_ptr<internal::subchannel>> m_subchannels{};
      std::map<std::uint16_t, std::shared_ptr<service_component>> m_components{};

      std::shared_ptr<service> m_activeService{};

      std::string m_label{};
      std::uint16_t m_id{};

      std::atomic_bool m_aborted{};

      friend internal::fic_parser;
    };

  }

#endif
