/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Cook
*/

#include "Cook.hpp"
#include <unistd.h>
#include <chrono>

namespace Plazza
{
Cook::Cook()
{
    this->busy.store(false);
}
Cook::~Cook()
{
    if (this->t.joinable())
        this->t.join();
}

bool Cook::isBusy() noexcept
{
    return this->busy.load() == true ? true : false;
}

void Cook::bake(int timeMs) noexcept
{
    this->busy.store(true);
    t = std::thread(&Cook::baking, this, timeMs);
    t.join();
}

void Cook::baking(int time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    this->busy.store(false);
}
}
