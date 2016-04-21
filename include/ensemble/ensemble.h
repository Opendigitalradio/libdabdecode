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

  struct ensemble
    {
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

