/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Mutex
*/

#pragma once

namespace Plazza {
class Mutex {
  public:
    Mutex() = default;
    Mutex(Mutex const& to_copy) = default;
    Mutex(Mutex&& to_move) = default;

    ~Mutex() = default;

    Mutex& operator=(Mutex const& to_copy) = default;

    void lock();
    void unlock();
    void trylock();
  private:
};
}
