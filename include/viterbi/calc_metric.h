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

#ifndef __DABDECODE_VITERBI__CALC_METRIC
#define __DABDECODE_VITERBI__CALC_METRIC

#include <vector>

namespace dabdecode
  {

  template <class T>
  void calc_metric(int O, int D, const std::vector<T> &TABLE, const T *input, float *metric)
    {
    for(int o = 0; o < O; o++)
      {
      metric[o] = 0.0;

      for(int m = 0; m < D; m++)
        {
        T s = input[m]-TABLE[o*D+m];
        metric[o] += s * s;
        }
      }
    }

  }

#endif

