/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <thread>

#include "Cook.hpp"
#include "FoodStock.hpp"
#include "MultiThread/SafeQueue.hpp"
#include "Pizza.hpp"

namespace Plazza
{
class Kitchen {
  public:
    Kitchen(float multiplier, unsigned int chefs_nbr,
            unsigned int stock_refill_time);
    Kitchen(Kitchen const& to_copy) = delete;
    Kitchen(Kitchen&& to_move) = delete;

    ~Kitchen()
    {
        t.join();
    }

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
    void stop() noexcept { this->running = false; }
    std::vector<Cook> Cooks;
    void run();

  private:
    bool CookManager(std::tuple<Pizza, Ingredients_t, int>);
    /*
     * create a thread with given function, and self
     */
    /*
     * have a clock, and call for refill every x ms
     */
    bool tryRefill() noexcept;
    SafeQueue<Pizza> Queue;
    int pizzaNb = 0;
    bool running = true;
    const int cookNb = 0;
    const int refillTime;
    const int CookTimeMultiplier;
    std::thread t;
    FoodStock Stock;
};
} // namespace Plazza
