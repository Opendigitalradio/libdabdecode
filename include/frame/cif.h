#ifndef __DABDECODE_FRAME__CIF
#define __DABDECODE_FRAME__CIF

#include <vector>

namespace dabdecode
  {

  /**
   * @internal
   *
   * @brief This call represents a Common Interleaved Frame (CIF)
   *
   * A CIF conatains the Capacity Units (CUs) which in turn contain the data that
   * is being transported in different subchannels. The subchannel data is
   * time-interleaved thus the I in CIF.
   *
   * This calls is designed as an overlay. It only stores iterators
   * marking the begin and end of the range of bytes that represent a CIF. The creator/user
   * must guarantee that the ramge remains valid while the CIF is in use.
   *
   * @note Contrary to a @ref fib which is an overlay for already decoded bytes, the CIF is an
   * overlay for non-decoded samples since decoding can only happen in conjunction with the
   * information of a @ref subchannel.
   */
  struct cif
    {
    using iterator = std::vector<float>::const_iterator;

    cif(iterator const & begin, iterator const & end);

    iterator begin() const;
    iterator end() const;

    private:
      iterator const m_begin;
      iterator const m_end;
    };

  }

#endif

