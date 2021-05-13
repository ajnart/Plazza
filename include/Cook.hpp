/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Cook
*/

#pragma once

#include <mutex>
#include <thread>
#include <atomic>
#include "Pizza.hpp"

namespace Plazza {
class Cook {
  public:
    Cook();
    Cook(Cook const& to_copy) = delete;
    Cook(Cook&& to_move) = delete;

    ~Cook();

    Cook& operator=(Cook const& to_copy) = delete;

    void bake(int timeMs, Pizza pizza) noexcept;
    bool isBusy() noexcept;

  private:
    Pizza pizza;
    void baking(int time);
    std::atomic_bool busy;
    std::thread t;
};

}
