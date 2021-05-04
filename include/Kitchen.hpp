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

    /*
     * return occupancy of the cooks, and stock of ingredients
     */
    /* smth */ void status();
    /*
     * get the number of pizzas currently in the kitchen
     */
    int getPizzaNbr();
    /*
     * try to add a pizza to the queue. is kitchen is full, return false
     */
    bool addPizza(Pizza pizza);

  private:
    /*
     * create a thread with given function, and self
     */
    void run();
    /*
     * have a clock, and call for refill every x ms
     */
    bool tryRefill();
    SafeQueue<Pizza> Queue;

    int pizzaNb = 0;
    const int cookNb = 0;
    const int refillTime;
    const int CookTimeMultiplier;
    std::thread t;
    FoodStock Stock;
};
} // namespace Plazza
