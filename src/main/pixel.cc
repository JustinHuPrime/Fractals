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

#include "pixel.h"

#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

namespace fractals {
static_assert(sizeof(Pixel) == 3);

Pixel &Pixel::operator+=(Pixel const &other) noexcept {
  r = min(r + other.r, 255);
  g = min(g + other.g, 255);
  b = min(b + other.b, 255);
  return *this;
}
Pixel &Pixel::operator*=(double d) noexcept {
  r = min(round(r * d), 255.0);
  g = min(round(g * d), 255.0);
  b = min(round(b * d), 255.0);
  return *this;
}
Pixel operator+(Pixel const &l, Pixel const &r) noexcept {
  Pixel retval = l;
  retval += r;
  return retval;
}
Pixel operator*(double d, Pixel const &p) noexcept {
  Pixel retval = p;
  retval *= d;
  return retval;
}
Pixel operator*(Pixel const &p, double d) noexcept { return d * p; }
Pixel lerp(double t, Pixel const &a, Pixel const &b) noexcept {
  assert(0 <= t && t <= 1);
  return (1 - t) * a + t * b;
}
}  // namespace fractals
