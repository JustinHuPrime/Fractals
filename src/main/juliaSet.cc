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

#include "juliaSet.h"

#include <memory>

#include "pixel.h"
#include "stb_image_write.h"
#include "threadPool.h"

using namespace std;

namespace fractals {
namespace {
constexpr size_t SIZE = 4096;
constexpr size_t MAX_ITER = 10'000;
}  // namespace

void juliaSet(complex<double> c) noexcept {
  unique_ptr<Pixel[]> image = make_unique<Pixel[]>(SIZE * SIZE);
  ThreadPool pool;

  for (size_t y = 0; y < SIZE; ++y) {
    pool([y, &image, &c]() {
      for (size_t x = 0; x < SIZE; ++x) {
        complex<double> z =
            complex<double>(static_cast<double>(x) / SIZE * 4 - 2,
                            -(static_cast<double>(y) / SIZE * 4 - 2));

        size_t iterCount = 0;
        while (norm(z) < 4 && iterCount < MAX_ITER) {
          z = z * z + c;
          ++iterCount;
        }

        if (iterCount == MAX_ITER) {
          image[x + y * SIZE] = BLACK;
        } else {
          if (iterCount == 0) {
            iterCount = 1;
          }
          double iterLog = log10(iterCount) / log10(MAX_ITER) * 6;
          // 0-1 = BLUE
          // 1-2 = LIGHT_BLUE
          // 2-3 = WHITE
          // 3-4 = YELLOW
          // 4-5 = ORANGE
          // 5-6 = RED
          // 6+ = BLACK
          if (0 <= iterLog && iterLog <= 1) {
            image[x + y * SIZE] = lerp(iterLog, BLUE, LIGHT_BLUE);
          } else if (1 <= iterLog && iterLog <= 2) {
            image[x + y * SIZE] = lerp(iterLog - 1, LIGHT_BLUE, WHITE);
          } else if (2 <= iterLog && iterLog <= 3) {
            image[x + y * SIZE] = lerp(iterLog - 2, WHITE, YELLOW);
          } else if (3 <= iterLog && iterLog <= 4) {
            image[x + y * SIZE] = lerp(iterLog - 3, YELLOW, ORANGE);
          } else if (4 <= iterLog && iterLog <= 5) {
            image[x + y * SIZE] = lerp(iterLog - 4, ORANGE, RED);
          } else if (5 <= iterLog && iterLog <= 6) {
            image[x + y * SIZE] = lerp(iterLog - 5, RED, BLACK);
          } else {
            image[x + y * SIZE] = MAGENTA;
          }
        }
      }
    });
  }

  pool.join();

  stbi_write_png("julia-set.png", SIZE, SIZE, 3, image.get(), 0);
}
}  // namespace fractals
