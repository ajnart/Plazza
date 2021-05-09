/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Cook
*/

#include "Cook.hpp"
#include <unistd.h>
#include <chrono>
#ifdef __DEBUG
#include <iostream>
#endif

namespace Plazza
{
Cook::~Cook()
{
    if (this->t.joinable())
        this->t.join();
}

bool Cook::isBusy() noexcept
{
#ifdef __DEBUG
    std::cout << (this->busy.load() ? "Cook is busy." : "Cook is free.") << std::endl;
#endif
    /* bool result = m.try_lock(); */
    /* if (result == true) */
    /*     m.unlock(); */
    /* return result; */
    return this->busy.load();
}

void Cook::bake(int timeMs) noexcept
{
#ifdef __DEBUG
    std::cout << "a cook is going to cook for " << timeMs / 1000 << "s!" << std::endl;
#endif
    this->busy.store(true, std::memory_order_relaxed);
#ifdef __DEBUG
    std::cout << (this->busy.load() ? "YES" : "FUCK") << std::endl;
#endif
    /* m.lock(); */
    t = std::thread(&Cook::baking, this, timeMs);
}

void Cook::baking(int time)
{
#ifdef __DEBUG
    std::cout << "sleeping for " << time / 1000 << "s!" << std::endl;
#endif
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    this->busy.store(false, std::memory_order_relaxed);
    /* m.unlock(); */
}
}
