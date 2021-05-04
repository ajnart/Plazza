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

namespace Plazza
{
class Kitchen {
  public:
    Kitchen(int cookNb, int refillTime, int CookTimeMultiplier) :
        cookNb(cookNb),
        refillTime(refillTime),
        CookTimeMultiplier(CookTimeMultiplier),
        t(&Kitchen::run, this)
    {}
    Kitchen(Kitchen const& to_copy) = delete;
    Kitchen(Kitchen&& to_move) = delete;

    ~Kitchen() = default;

    Kitchen& operator=(Kitchen const& to_copy) = delete;

    bool isKitchenFull();
    int getPizzaNb();
    /*
     * return occupancy of the cooks, and stock of ingredients
     */
    /* smth */ void status();
    /*
     * have a clock, and call for refill every x ms
     */
    /*
     * create a thread with given function, and self
     */

  private:
    void run();
    bool tryRefill();
    int pizzaNb = 0;
    const int cookNb = 0;
    const int refillTime;
    const int CookTimeMultiplier;
    std::thread t;
    SafeQueue<int/*Pizza Class type*/> queue;
};
} // namespace Plazza
