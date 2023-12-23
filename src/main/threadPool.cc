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

#include "threadPool.h"

#include <chrono>

using namespace std;

namespace fractals {
ThreadPool::NotifyingThread::NotifyingThread(
    function<void()> const &fn) noexcept
    : joinableFlag(false), thread([this, fn]() {
        fn();
        joinableFlag = true;
      }) {}
bool ThreadPool::NotifyingThread::joinable() const noexcept {
  return joinableFlag;
}
void ThreadPool::NotifyingThread::join() noexcept { return thread.join(); }

ThreadPool::ThreadPool() noexcept
    : ThreadPool(thread::hardware_concurrency() * NUM_THREADS_PER_CORE) {}
ThreadPool::ThreadPool(size_t numThreads) noexcept
    : numThreads(numThreads), threads() {}

void ThreadPool::operator()(function<void()> const &fn) noexcept {
  if (threads.size() < numThreads) {
    threads.emplace_back(make_unique<NotifyingThread>(fn));
  } else {
    while (true) {
      // try to insert one
      for (auto iter = threads.begin(); iter != threads.end(); ++iter) {
        if ((*iter)->joinable()) {
          *iter = make_unique<NotifyingThread>(fn);
          return;
        }
      }

      // wait a bit, try again
      this_thread::sleep_for(100ms);
    }
  }
}
void ThreadPool::join() noexcept {
  for_each(threads.begin(), threads.end(),
           [](unique_ptr<NotifyingThread> &t) { t.reset(); });
}
}  // namespace fractals
