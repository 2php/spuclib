#ifndef SPUC_EQUALIZER
#define SPUC_EQUALIZER

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
// from directory: spuc_classes
#include <spuc/spuc_types.h>
#include <spuc/spuc_types.h>
#include <spuc/complex.h>
#include <vector>
#include <spuc/iir_allpass_variable_cascade.h>
namespace SPUC {

class equalizer {
 public:
  typedef complex<double> audio_data_type;
  int num_bands;
  std::vector<iir_allpass_variable_cascade<audio_data_type, double> > S_All;
  std::vector<audio_data_type> fil_out;
  std::vector<audio_data_type> eq;
  std::vector<double> levels;
  audio_data_type lpf;
  std::vector<double> gains;
  double lev_gain;
  long count;

  void adjust_level(int filt_num, double gain);

  equalizer(int BANDS = 10);
  void init(int points) { ; }
  void set_fs(double f) { ; }
  void reset();
  complex<double> run(const complex<double>& sample);
  void update_levels();
  void get_levels(float* levs);
  void get_gains(float* gains);
  float get_level(int band) {
    if (band < num_bands)
      return ((float)levels[band]);
    else
      return (0);
  }
  float get_gain(int band) {
    if (band < num_bands) return ((float)gains[band]);
    return (0);
  }
};
}  // namespace SPUC
#endif
