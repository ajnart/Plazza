/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Cook
*/

#pragma once

#include <thread>

class Cook {
  public:
    Cook(int timeMs) : t(&Cook::cook, this, timeMs)
    {}
    Cook(Cook const& to_copy) = delete;
    Cook(Cook&& to_move) = delete;

    ~Cook() = default;

    Cook& operator=(Cook const& to_copy) = delete;

    void cook(int timeMs);

  private:
    std::thread t;
};

