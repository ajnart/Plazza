/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** SafeQueue
*/

#pragma once
#include <mutex>
#include <queue>

template <typename T>
class SafeQueue {
  public:
    SafeQueue() = default;
    SafeQueue(SafeQueue const& to_copy) = delete;
    SafeQueue(SafeQueue&& to_move) = delete;

    ~SafeQueue() = default;

    SafeQueue& operator=(SafeQueue const& to_copy) = delete;

    void push(T value)
    {
        std::unique_lock<std::mutex> ul(this->m);

        queue.push(value);
    }
    /*
     * try to pop an element from the queue, and store it in value
     */
    bool tryPop(T& value)
    {
        std::unique_lock<std::mutex> ul(this->m);

        if (!m.try_lock()) {
            return false;
        }
        if (this->queue.empty())
            return false;
        value = this->queue.front();
        this->queue.pop();
        return true;
    }

  private:
    std::queue<T> queue;
    std::mutex m;
};
