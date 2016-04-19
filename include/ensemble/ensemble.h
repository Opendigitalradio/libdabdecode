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

    std::string const & name() const;
    std::uint16_t id() const;

    void update();

    explicit operator bool() const;

    void handle(struct fig_0 const & mci);
    void handle(struct fig_1 const & label);

    private:
      bool next_frame();

      std::istream & m_sync;
      std::istream & m_data;
      transport_mode const m_mode;

      std::unique_ptr<frame> m_frame{};

      std::string m_name;
      std::uint16_t m_id;
    };

  }

#endif

