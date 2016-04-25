#ifndef __DABDECODE_ENSEMBLE__ENSEMBLE
#define __DABDECODE_ENSEMBLE__ENSEMBLE

#include "ensemble/subchannel.h"
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

    std::string const & label() const;
    std::uint16_t id() const;
    std::set<subchannel> const & subchannels() const;

    void update();

    explicit operator bool() const;

    private:
      bool next_frame();

      void label(std::string const & label);
      void id(std::uint16_t const id);
      void add(subchannel && subchannel);

      std::istream & m_sync;
      std::istream & m_data;
      transport_mode const m_mode;

      fic_parser m_ficParser{*this};
      std::unique_ptr<frame> m_frame{};
      std::set<subchannel> m_subchannels{};
      std::string m_label{};
      std::uint16_t m_id{};

      friend fic_parser;
    };

  }

#endif

