/* -*- c++ -*- */
/*
 * Copyright 2004,2012 Free Software Foundation, Inc.
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

#ifndef DAB_VITERBI_CORE_ALGORITHMS
#define DAB_VITERBI_CORE_ALGORITHMS

#include <cstdint>
#include <vector>

namespace dab
  {

  namespace internal
    {

    void viterbi_algorithm_combined(int I,
                                    int S,
                                    int O,
                                    const std::vector<int> &OS,
                                    const std::vector< std::vector<int> > &PS,
                                    const std::vector< std::vector<int> > &PI,
                                    int K,
                                    int S0,
                                    int SK,
                                    int D,
                                    const float *in,
                                    uint8_t *out);
    }

  }

#endif

