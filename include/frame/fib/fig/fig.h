#ifndef __DABDECODE_FRAME_FIB_FIG__FIG
#define __DABDECODE_FRAME_FIB_FIG__FIG

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <vector>

namespace dabdecode
  {

  struct fig
    {
    fig(std::vector<uint8_t> const & data);

    virtual ~fig() = default;

    std::size_t length() const;

    protected:
      std::vector<uint8_t> const m_dataField;
    };

  /*
   * @internal
   *
   * Create a dynamically typed concrete fig from the supplied data.
   */
  std::shared_ptr<fig> make_fig(std::vector<uint8_t> const & data);
  }

#endif

