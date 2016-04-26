#ifndef __DABDECODE_PARSER__FIC_PARSER
#define __DABDECODE_PARSER__FIC_PARSER

#include "frame/fib.h"

#include <vector>

namespace dabdecode
  {

  struct ensemble;

  struct fic_parser
    {
    explicit fic_parser(ensemble & target);

    void parse(std::vector<fib> const & fic);

    private:
      using iterator = fib::iterator;

      void fig_0(iterator const & base, iterator const & end);
      void fig_0_ext_0(iterator const & base);
      void fig_0_ext_1(iterator const & base, iterator const & end);
      void fig_0_ext_2(iterator const & base, iterator const & end, bool isData);

      void fig_1(iterator const & base);
      void fig_1_ext_0(iterator const & base);

      ensemble & m_target;
    };

  }

#endif

