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

#ifndef FRACTALS_THREAD_POOL_H_
#define FRACTALS_THREAD_POOL_H_

#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

namespace fractals {
class ThreadPool {
 private:
  class NotifyingThread {
   public:
    explicit NotifyingThread(std::function<void()> const &) noexcept;
    NotifyingThread(NotifyingThread const &) noexcept = delete;
    NotifyingThread(NotifyingThread &&) noexcept = delete;

    ~NotifyingThread() noexcept = default;

    NotifyingThread &operator=(NotifyingThread const &) noexcept = delete;
    NotifyingThread &operator=(NotifyingThread &&) noexcept = delete;

    bool joinable() const noexcept;
    void join() noexcept;

   private:
    std::atomic<bool> joinableFlag;
    std::jthread thread;
  };

 public:
  static constexpr size_t NUM_THREADS_PER_CORE = 4;

  ThreadPool() noexcept;
  explicit ThreadPool(size_t numThreads) noexcept;
  ThreadPool(ThreadPool const &) noexcept = delete;
  ThreadPool(ThreadPool &&) noexcept = default;

  ~ThreadPool() noexcept = default;

  ThreadPool &operator=(ThreadPool const &) noexcept = delete;
  ThreadPool &operator=(ThreadPool &&) noexcept = default;

  void operator()(std::function<void()> const &) noexcept;
  void join() noexcept;

 private:
  size_t numThreads;
  std::vector<std::unique_ptr<NotifyingThread>> threads;
};
}  // namespace fractals

#endif  // FRACTALS_THREAD_POOL_H_
