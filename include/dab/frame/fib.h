#ifndef DABDECODE_FRAME_FIB
#define DABDECODE_FRAME_FIB

#include <cstdint>
#include <iosfwd>
#include <memory>
#include <vector>

namespace dab
  {

  namespace internal
    {

    /**
     * @internal
     * @author Felix Morgner
     *
     * @brief This class represents a Fast Information Block (FIB)
     *
     * A FIB contains a number of Fast Information Groups (FIGs) which provide information
     * of the ensemble itself as well as the structure und information related to the different
     * services carried in an ensemble.
     *
     * This class is designed as an overlay. It only stores iterators marking the
     * begin and end of the range of bytes that make up a FIB. The creator/user must thus guarantee
     * that the range remains valid while the FIB is in use.
     */
    struct fib
      {
      using iterator = std::vector<std::uint8_t>::const_iterator;

      fib(iterator const & begin, iterator const & end);

      operator bool() const;

      iterator begin() const;
      iterator end() const;

      private:
        iterator const m_begin;
        iterator const m_end;
      };

    }

  }

#endif
