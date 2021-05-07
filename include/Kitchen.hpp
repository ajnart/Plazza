/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <thread>

#include "ArgParse.hpp"
#include "Cook.hpp"
#include "FoodStock.hpp"
#include "MultiThread/NamedPipe.hpp"
#include "MultiThread/SafeQueue.hpp"
#include "Pizza.hpp"

namespace Plazza
{
class Kitchen {
  public:
    Kitchen(params_t params, int id);
    Kitchen(Kitchen const& to_copy) = delete;
    Kitchen(Kitchen&& to_move) = default;

    ~Kitchen();

    Kitchen& operator=(Kitchen const& to_copy) = delete;
    Kitchen& operator=(Kitchen&& to_move) = delete;

    /*
     * main function of the kitchen, the one to call after fork()
     */
    void run();

  private:
    /*
     * print occupancy of the cooks, and stock of ingredients
     */
    void status() noexcept;
    /*
     * get the number of pizzas currently in the kitchen, and send the result
     * througt the write pipe.
     */
    void getPizzaNbr() noexcept;
    /*
     * read pizza name from [name] and try to save it in the queue. Send TRUE if
     * the kitchen can handle the command, FALSE otherwise.
     */
    void handlePizza(const std::string& name);

    /* void stop() noexcept */
    /* { */
    /*     this->running = false; */
    /* } */

    bool getlineAsync();

    bool CookManager(std::tuple<Pizza, Ingredients_t, int>);
    /*
     * create a thread with given function, and self
     */
    /*
     * have a clock, and call for refill every x ms
     */
    std::vector<Cook> Cooks;
    bool tryRefill() noexcept;
    // SafeQueue<Pizza> Queue;
    int pizzaNb = 0;
    const int cookNb = 0;
    const int refillTime;
    const int CookTimeMultiplier;
    NamedPipe write;
    int id;
    NamedPipe read;
    std::queue<Pizza> queue;
    // std::thread t;
    FoodStock Stock;
};
} // namespace Plazza
