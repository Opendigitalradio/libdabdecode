#ifndef __DABDECODE_ENSEMBLE__ENSEMBLE
#define __DABDECODE_ENSEMBLE__ENSEMBLE

#include "ensemble/subchannel.h"
#include "ensemble/service.h"
#include "frame/frame.h"
#include "mode/transport_mode.h"
#include "parser/fic_parser.h"

#include <cstdint>
#include <iosfwd>
#include <string>
#include <memory>
#include <set>

namespace dabdecode
  {

  /**
   * @brief Access information and data of a DAB ensemble
   *
   * This class provides acces to the information and data of a
   * DAB ensemble. It gives access to services and subchannels.
   */
  struct ensemble
    {
    /**
     * @brief Construct a @ref ensemble from a synchronization and a data stream.
     *
     * An ensemble is the most basic and interesting entity exposed by libdabdecode.
     * It provides access to data services and audio services, also called programmes.
     * The synchronization stream @p sync is expected to contain "zero" bytes unless
     * the begin of a frame is reached. The data stream on the other hand must contain
     * a single-precision 32-bit foating point stream of OFDM symbols. The transmission
     * mode can be specified vi the @p mode argument, which default to DAB TM 1.
     *
     * @param sync The synchronization stream
     * @param data The OFDM symbol data stream
     * @param mode The transmission mode used for the ensemble
     */
    ensemble(std::istream & sync, std::istream & data, transport_mode const mode = transport_mode::mode_1);

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
    std::set<service> const & services() const;

    /**
     * @brief Update the ensemble
     *
     * This function updates an ensemble from the datastream supplied during
     * construction. This includes updating the currently active service.
     */
    void update();

    /**
     * @brief Activate a service for decoding
     *
     * This function activates a service for decoding. The reference to the
     * service might be obtained via the function #services.
     *
     * @see #services
     */
    void activate(service const & service);

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
       * It assembles the whole frame and stores it in #m_frame.
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
      void add(subchannel && subchannel);

      /**
       * @internal
       *
       * @brief Add a service to the ensemble
       */
      void add(service && service);

      std::istream & m_sync;
      std::istream & m_data;
      transport_mode const m_mode;

      fic_parser m_ficParser{*this};
      std::unique_ptr<frame> m_frame{};
      std::set<subchannel> m_subchannels{};
      std::set<service> m_services{};
      std::string m_label{};
      std::uint16_t m_id{};

      service * m_activeService{};

      friend fic_parser;
    };

  }

#endif

