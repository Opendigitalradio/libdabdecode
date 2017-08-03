/* -*- c++ -*- */
/*
 * Copyright 2002,2012 Free Software Foundation, Inc.
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

#include "dab/viterbi/fsm.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>

namespace dab
  {

  namespace internal
    {

    bool dec2base(unsigned int num, int base, std::vector<int> &s)
      {
      int l = s.size();
      unsigned int n=num;

      for(int i=0;i<l;i++)
        {
        s[l-i-1] = n % base;
        n /= base;
        }

      if(n!=0)
        {
        printf("Number %d requires more than %d digits.",num,l);
        return false;
        }

      return true;
      }

    unsigned int base2dec(const std::vector<int> &s, int base)
      {
      int l = s.size();
      unsigned int num=0;

      for(int i=0;i<l;i++)
        {
        num=num*base+s[i];
        }

      return num;
      }

    bool dec2bases(unsigned int num, const std::vector<int> &bases, std::vector<int> &s)
      {
      int l = s.size();
      unsigned int n=num;

      for(int i=0;i<l;i++)
        {
        s[l-i-1] = n % bases[l-i-1];
        n /= bases[l-i-1];
        }

      if(n!=0)
        {
        printf("Number %d requires more than %d digits.",num,l);
        return false;
        }

      return true;
      }

    unsigned int
      bases2dec(const std::vector<int> &s, const std::vector<int> &bases)
        {
        int l = s.size();
        unsigned int num=0;

        for(int i=0;i<l;i++)
          {
          num = num * bases[i] + s[i];
          }

        return num;
        }

    fsm::fsm(int k, int n, const std::array<int, 4> &G)
      {
      std::vector<int> max_mem_x(k,-1);
      int max_mem = -1;

      for(int i=0;i<k;i++)
        {
        for(int j=0;j<n;j++)
          {
          int mem = -1;
          if(G[i*n+j]!=0)
            {
            mem=(int)(log(double(G[i*n+j]))/log(2.0));
            }
          if(mem>max_mem_x[i])
            {
            max_mem_x[i]=mem;
            }
          if(mem>max_mem)
            {
            max_mem=mem;
            }
          }
        }

      int sum_max_mem = 0;

      for(int i=0;i<k;i++)
        {
        sum_max_mem += max_mem_x[i];
        }

      d_I=1<<k;
      d_S=1<<sum_max_mem;
      d_O=1<<n;

      std::vector<std::vector<int> > Gb(k*n);
      for(int j=0;j<k*n;j++)
        {
        Gb[j].resize(max_mem+1);
        dec2base(G[j],2,Gb[j]);
        }

      std::vector<int> bases_x(k);
      for(int j=0;j<k ;j++)
        {
        bases_x[j] = 1 << max_mem_x[j];
        }

      d_NS.resize(d_I*d_S);
      d_OS.resize(d_I*d_S);

      std::vector<int> sx(k);
      std::vector<int> nsx(k);
      std::vector<int> tx(k);
      std::vector<std::vector<int> > tb(k);
      for(int j=0;j<k;j++)
        {
        tb[j].resize(max_mem+1);
        }
      std::vector<int> inb(k);
      std::vector<int> outb(n);

      for(int s=0;s<d_S;s++)
        {
        dec2bases(s,bases_x,sx);

        for(int i=0;i<d_I;i++)
          {
          dec2base(i,2,inb);

          for(int j=0;j<k;j++)
            {
            nsx[j] = (inb[j]*bases_x[j]+sx[j])/2;
            }

          d_NS[s*d_I+i]=bases2dec(nsx,bases_x);

          for(int j=0;j<k;j++)
            {
            tx[j] = inb[j]*bases_x[j]+sx[j];
            }

          for(int j=0;j<k;j++)
            {
            dec2base(tx[j],2,tb[j]);
            }

          for(int nn=0;nn<n;nn++)
            {
            outb[nn] = 0;
            for(int j=0;j<k;j++)
              {
              for(int m=0;m<max_mem+1;m++)
                {
                outb[nn] = (outb[nn] + Gb[j*n+nn][m]*tb[j][m]) % 2;
                }
              }
            }
          d_OS[s*d_I+i] = base2dec(outb,2);
          }
        }

      generate_PS_PI();
      generate_TM();
      }


    void fsm::generate_PS_PI()
      {
      d_PS.resize(d_S);
      d_PI.resize(d_S);

      for(int i=0;i<d_S;i++)
        {
        d_PS[i].resize(d_I*d_S);
        d_PI[i].resize(d_I*d_S);
        int j=0;

        for(int ii=0;ii<d_S;ii++) for(int jj=0;jj<d_I;jj++)
          {
          if(d_NS[ii*d_I+jj]!=i)
            {
            continue;
            }

          d_PS[i][j]=ii;
          d_PI[i][j]=jj;
          j++;
          }

        d_PS[i].resize(j);
        d_PI[i].resize(j);
        }
      }

    void fsm::generate_TM()
      {
      d_TMi.resize(d_S*d_S);
      d_TMl.resize(d_S*d_S);

      for(int i=0;i<d_S*d_S;i++)
        {
        d_TMi[i] = -1;
        d_TMl[i] = d_S;
        if (i/d_S == i%d_S)
          {
          d_TMl[i] = 0;
          }
        }

      for(int s=0;s<d_S;s++)
        {
        bool done = false;
        int attempts = 0;

        while (done == false && attempts < d_S-1)
          {
          done = find_es(s);
          attempts ++;
          }
        if (done == false && d_S > 1)
          {
          printf("fsm::generate_TM(): FSM appears to be disconnected\n");
          printf("state %d cannot be reached from all other states\n",s);
          }
        }
      }

    bool fsm::find_es(int es)
      {
      bool done = true;
      for(int s=0;s<d_S;s++)
        {
        if(d_TMl[s*d_S+es] < d_S)
          {
          continue;
          }

        int minl=d_S;
        int mini=-1;

        for(int i=0;i<d_I;i++)
          {
          if( 1 + d_TMl[d_NS[s*d_I+i]*d_S+es] < minl)
            {
            minl = 1 + d_TMl[d_NS[s*d_I+i]*d_S+es];
            mini = i;
            }
          }
        if (mini != -1)
          {
          d_TMl[s*d_S+es]=minl;
          d_TMi[s*d_S+es]=mini;
          }
        else
          {
          done = false;
          }
        }
      return done;
      }

    }

  }
