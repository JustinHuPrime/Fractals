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

#include "sierpinskiCarpet.h"

#include <cassert>
#include <cmath>
#include <memory>

#include "pixel.h"
#include "stb_image_write.h"

using namespace std;

namespace fractals {
namespace {
constexpr size_t SIZE = 4096;
}
void sierpinskiCarpet(size_t layers) noexcept {
  assert(layers >= 1);

  unique_ptr<Pixel[]> image = make_unique<Pixel[]>(SIZE * SIZE);

  for (size_t y = 0; y < SIZE; ++y) {
    for (size_t x = 0; x < SIZE; ++x) {
      bool isBlack = true;
      for (double layer = 0; layer < layers; ++layer) {
        // get part size and x, y coordinates within part
        double partSize = SIZE / pow(3, layer);
        double partX = fmod(x, partSize);
        double partY = fmod(y, partSize);
        // if x, y are both within the inner third, this is filled in
        if (partSize / 3 <= partX && partX <= 2 * partSize / 3 &&
            partSize / 3 <= partY && partY <= 2 * partSize / 3) {
          isBlack = false;
          break;
        }
      }
      image[x + y * SIZE] = isBlack ? BLACK : WHITE;
    }
  }

  stbi_write_png("sierpinski-carpet.png", 4096, 4096, 3, image.get(), 0);
}
}  // namespace fractals
