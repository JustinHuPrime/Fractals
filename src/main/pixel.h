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

#ifndef FRACTALS_PIXEL_H_
#define FRACTALS_PIXEL_H_

#include <cstdint>

namespace fractals {
struct Pixel {
  uint8_t r;
  uint8_t g;
  uint8_t b;

  constexpr Pixel() noexcept = default;
  constexpr Pixel(uint8_t r, uint8_t g, uint8_t b) noexcept
      : r(r), g(g), b(b) {}
  Pixel(Pixel const &) noexcept = default;
  Pixel(Pixel &&) noexcept = default;

  ~Pixel() noexcept = default;

  Pixel &operator=(Pixel const &) noexcept = default;
  Pixel &operator=(Pixel &&) noexcept = default;

  Pixel &operator+=(Pixel const &p) noexcept;
  Pixel &operator*=(double d) noexcept;
};
Pixel operator+(Pixel const &, Pixel const &) noexcept;
Pixel operator*(float, Pixel const &) noexcept;
Pixel operator*(Pixel const &, float) noexcept;
Pixel lerp(double t, Pixel const &a, Pixel const &b) noexcept;

constexpr Pixel BLACK = Pixel(0, 0, 0);
constexpr Pixel WHITE = Pixel(0xff, 0xff, 0xff);
constexpr Pixel BLUE = Pixel(0, 0, 0xff);
constexpr Pixel LIGHT_BLUE = Pixel(0, 0xdf, 0xff);
constexpr Pixel YELLOW = Pixel(0xff, 0xdd, 0x27);
constexpr Pixel ORANGE = Pixel(0xff, 0x6a, 0x00);
constexpr Pixel RED = Pixel(0xff, 0, 0);
constexpr Pixel MAGENTA = Pixel(0xff, 0, 0xff);
}  // namespace fractals

#endif  // FRACTALS_PIXEL_H_
