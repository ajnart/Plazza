/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** SafeQueue
*/

#pragma once
#include <queue>
#include "Mutex.hpp"

namespace Plazza {
class SafeQueue {
  public:
    SafeQueue() = default;
    SafeQueue(SafeQueue const& to_copy) = default;
    SafeQueue(SafeQueue&& to_move) = default;

    ~SafeQueue() = default;

    SafeQueue& operator=(SafeQueue const& to_copy) = default;

    void push(int value);
    /*
     * try to pop an element from the queue, and store it in value
     */
    bool tryPop(int &value);
  private:
    std::queue<Mutex> queue;
};
}
