/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include <chrono>
#include <unistd.h>

namespace Plazza
{
Kitchen::Kitchen(int cookNb, int refillTime, int CookTimeMultiplier) :
    cookNb(cookNb),
    refillTime(refillTime),
    CookTimeMultiplier(CookTimeMultiplier),
    t(&Kitchen::run, this)
{}

void Kitchen::status(void) noexcept
{
    return;
}

int Kitchen::getPizzaNbr() noexcept
{
    return this->pizzaNb;
}

bool Kitchen::addPizza(const Pizza& pizza) noexcept
{
    if (this->pizzaNb >= this->cookNb * 2)
        return false;
    this->Queue.push(pizza);
    return true;
}

void Kitchen::run()
{
    while (!this->stop) {
        sleep(1);
    }
}

bool Kitchen::tryRefill() noexcept
{
    static auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) >=
        std::chrono::milliseconds(this->refillTime)) {
        t1 = std::chrono::high_resolution_clock::now();
        this->Stock.refill();
        return true;
    }
    return false;
}

}
