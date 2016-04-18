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
  struct extension
    {
    extension(std::vector<uint8_t> const & data);
    virtual ~extension() = default;

    std::size_t length() const;

    protected:
      std::vector<uint8_t> const m_dataField;
    };

  }

#endif

