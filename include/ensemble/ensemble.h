#ifndef __DABDECODE_ENSEMBLE__ENSEMBLE
#define __DABDECODE_ENSEMBLE__ENSEMBLE

#include "frame/frame.h"
#include "mode/transport_mode.h"

#include <cstdint>
#include <iosfwd>
#include <string>
#include <memory>

namespace dabdecode
  {

  struct ensemble
    {
    ensemble(std::istream & sync, std::istream & data, transport_mode const mode = transport_mode::mode_1);

    std::string const & label() const;
    std::uint16_t id() const;

    void update();

    explicit operator bool() const;

    private:
      bool next_frame();

      void set_label(std::string && label);
      void set_id(std::uint16_t const id);

      std::istream & m_sync;
      std::istream & m_data;
      transport_mode const m_mode;

      std::unique_ptr<frame> m_frame{};

      std::string m_name;
      std::uint16_t m_id;

      friend struct fib_parser;
    };

  }

#endif

