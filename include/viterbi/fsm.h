/* -*- c++ -*- */
/*
 * Copyright 2002,2011-2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __DABDECODE_VITERBI__CORE_ALGORITHMS
#define __DABDECODE_VITERBI__CORE_ALGORITHMS

#include <vector>
#include <iosfwd>

namespace dabdecode
  {
  class fsm
    {
    int d_I;
    int d_S;
    int d_O;
    std::vector<int> d_NS;
    std::vector<int> d_OS;
    std::vector< std::vector<int> > d_PS;
    std::vector< std::vector<int> > d_PI;
    std::vector<int> d_TMl;
    std::vector<int> d_TMi;
    void generate_PS_PI ();
    void generate_TM ();
    bool find_es(int es);

    public:
      fsm(int k, int n, const std::vector<int> &G);

      int I() const { return d_I; }
      int S() const { return d_S; }
      int O() const { return d_O; }
      const std::vector<int> & NS() const { return d_NS; }
      const std::vector<int> & OS() const { return d_OS; }
      const std::vector< std::vector<int> > & PS() const { return d_PS; }
      const std::vector< std::vector<int> > & PI() const { return d_PI; }
      const std::vector<int> & TMi() const { return d_TMi; }
      const std::vector<int> & TMl() const { return d_TMl; }
    };
  }

#endif
