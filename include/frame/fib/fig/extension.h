#ifndef __DABDECODE_FRAME_FIB_FIG__EXTENSION
#define __DABDECODE_FRAME_FIB_FIG__EXTENSION

#include <cstdint>
#include <memory>
#include <vector>

namespace dabdecode
  {

  /*
   * @internal
   *
   * This is the common base for all FIG extensions. It provided common functinality
   * and storage for extension data.
   */
  struct basic_extension
    {
    basic_extension(uint8_t const id, std::vector<uint8_t> const & data);

    uint8_t id() const;

    protected:
      uint8_t const m_id;
      std::vector<uint8_t> const m_dataField;
    };

  /*
   * @internal
   *
   * Create a dynamically typed extension based on the received data
   */
  std::shared_ptr<basic_extension> make_extension(std::vector<uint8_t> const & data);

  }

#endif

