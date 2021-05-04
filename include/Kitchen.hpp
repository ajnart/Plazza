/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <thread>

#include "FoodStock.hpp"
#include "MultiThread/SafeQueue.hpp"
#include "Pizza.hpp"

namespace Plazza
{
class Kitchen {
  public:
    Kitchen(int cookNb, int refillTime, int CookTimeMultiplier);
    Kitchen(Kitchen const& to_copy) = delete;
    Kitchen(Kitchen&& to_move) = delete;

    ~Kitchen() = default;

    Kitchen& operator=(Kitchen const& to_copy) = delete;

    /*
     * return occupancy of the cooks, and stock of ingredients
     */
    /* smth */ void status() noexcept;
    /*
     * get the number of pizzas currently in the kitchen
     */
    int getPizzaNbr() noexcept;
    /*
     * try to add a pizza to the queue. is kitchen is full, return false
     */
    bool addPizza(const Pizza& pizza) noexcept;

  private:
    /*
     * create a thread with given function, and self
     */
    void run();
    /*
     * have a clock, and call for refill every x ms
     */
    bool tryRefill() noexcept;
    SafeQueue<Pizza> Queue;
    bool stop = false;
    int pizzaNb = 0;
    const int cookNb = 0;
    const int refillTime;
    const int CookTimeMultiplier;
    std::thread t;
    FoodStock Stock;
};
} // namespace Plazza
