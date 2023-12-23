// Copyright 2023 Justin Hu
//
// This file is part of Fractals.
//
// Fractals is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// Fractals is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// Fractals. If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <iostream>

#include "juliaSet.h"
#include "sierpinskiCarpet.h"

using namespace std;
using namespace fractals;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    // require at least "./fractals <name of fractal>"
    cerr << "usage: " << argv[0] << " <fractal name> [args...]" << endl;
    return EXIT_FAILURE;
  }

  if (argv[1] == "sierpinski-carpet"s) {
    if (argc != 3) {
      cerr << "usage: " << argv[0] << " " << argv[1] << " <steps>" << endl;
      return EXIT_FAILURE;
    }
    sierpinskiCarpet(strtoull(argv[2], nullptr, 10));
  } else if (argv[1] == "julia-set"s) {
    if (argc != 4) {
      cerr << "usage: " << argv[0] << " " << argv[1] << " <real> <imaginary>"
           << endl;
      return EXIT_FAILURE;
    }
    juliaSet(
        complex<double>(strtod(argv[2], nullptr), strtod(argv[3], nullptr)));
  } else {
    cerr << "error: " << argv[1] << " is not a valid fractal name" << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
