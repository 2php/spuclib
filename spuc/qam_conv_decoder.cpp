
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
//! \author Tony Kirke
// from directory: spuc_src
#include <spuc/qam_soft_decision.h>
#include <spuc/qam_conv_decoder.h>
namespace SPUC {

// Create puncture inputs for Viterbi
void qam_conv_decoder::clear_soft_decision(long rate)
{
  if (rate) {
	for (int i=0;i<2*rate;i++) viterbi_input[i] =  0; 
  } else {
	viterbi_input[0] = 0; // bpsk
  }
}
// Data decoder
bool qam_conv_decoder::data_decode(complex<long> data_in)
{
  int j;
  qam_data_demap(rate_index, data_in, soft_decision_level, viterbi_input);

  // check viterbi_ready & viterbi_data for outputs
  for (j=0;j<rx_bits_per_symbol;j++) {
	if (no_conv) {
	  viterbi_ready = 1;
	  viterbi_data = (viterbi_input[j]<0) ? 1:0;
	} else {
	  viterbi_data = viterbi_decoder.depuncture(enc_rate,viterbi_input[j]);
	  viterbi_ready = viterbi_decoder.output_ready;
	}
  }
  //  bool ready = viterbi_ready;
  return(viterbi_data);
}
} // namespace SPUC
