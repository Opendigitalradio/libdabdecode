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

#include "dab/viterbi/calc_metric.h"
#include "dab/viterbi/core_algorithms.h"

namespace dab
  {

  namespace internal
    {

    void viterbi_algorithm_combined(int I, int S, int O,
                               const std::vector<int> &OS,
                               const std::vector< std::vector<int> > &PS,
                               const std::vector< std::vector<int> > &PI,
                               int K,
                               int S0,int SK,
                               int D,
                               const float *in, uint8_t *out)
      {
      static const float INF = 1.0e9;

      std::vector<int> trace(S*K);
      std::vector<float> alpha(S*2);
      float *metric = new float[O];
      int alphai;
      float norm,mm,minm;
      int minmi;
      int st;

      if(S0<0)
        {
        for(int i=0;i<S;i++) alpha[0*S+i]=0;
        }
      else
        {
        for(int i=0;i<S;i++) alpha[0*S+i]=INF;
        alpha[0*S+S0]=0.0;
        }

      alphai=0;
      for(int k=0;k<K;k++)
        {
        calc_metric(O, D, &(in[k*D]), metric);
        norm=INF;
        for(int j=0;j<S;j++)
          {
          minm=INF;
          minmi=0;
          for(unsigned int i=0;i<PS[j].size();i++)
            {
            if((mm=alpha[alphai*S+PS[j][i]]+metric[OS[PS[j][i]*I+PI[j][i]]])<minm)
              {
              minm=mm,minmi=i;
              }
            }
          trace[k*S+j]=minmi;
          alpha[((alphai+1)%2)*S+j]=minm;
          if(minm<norm)
            {
            norm=minm;
            }
          }
        for(int j=0;j<S;j++)
          {
          alpha[((alphai+1)%2)*S+j]-=norm;
          }

        alphai=(alphai+1)%2;
        }

      if(SK<0)
        {
        minm=INF;
        minmi=0;

        for(int i=0;i<S;i++)
          {
          if((mm=alpha[alphai*S+i])<minm)
            {
            minm=mm;
            minmi=i;
            }
          }

        st=minmi;
        }
      else
        {
        st=SK;
        }

      for(int k=K-1;k>=0;k--)
        {
        int i0=trace[k*S+st];
        out[k]= (uint8_t) PI[st][i0];
        st=PS[st][i0];
        }

      delete [] metric;
      }

    }

  }
