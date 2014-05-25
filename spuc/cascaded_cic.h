#ifndef SPUC_CASCADED_CIC
#define SPUC_CASCADED_CIC

/*
    Copyright (C) 2014 Tony Kirke

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// from directory: spuc_templates
#include <spuc/spuc_types.h>
#include <spuc/delay.h>
#include <spuc/cic.h>
namespace SPUC {

//! \file
template<class Numeric> class cascaded_cic 
{
protected:
  long rate; 
  char stages;
  int dump_count;
  cic<Numeric> cic1;
  cic<Numeric> cic2;
public:                         
  // Constructor
  cascaded_cic(char n=2, long r=4) : rate(r), stages(n)
  {
    int stages1 = stages/2 + (stages%2);
    cic1.num_stages(stages1);
    cic2.num_stages(stages/2);
    dump_count=0;
  }
  // To change the number of stages dynamically
  void num_stages(char stages,long r)
  {
   int stages1 = stages/2 + (stages%2);
    cic1.num_stages(stages1);
    cic2.num_stages(stages/2);
    rate = r;
    dump_count=0;
  }
  void reset() {
    cic1.reset();
    cic2.reset();
    dump_count=0;
  }
  Numeric clock(Numeric in)
  {
    int dump;
    if (dump_count == rate) {
      dump = 1;
      dump_count=0;
    } else dump = 0;
    in = cic1.decimate(in,dump);
    in = cic2.interpolate(in,dump);
    dump_count++;
	  return(in);
  }
};


} // namespace SPUC
#endif
