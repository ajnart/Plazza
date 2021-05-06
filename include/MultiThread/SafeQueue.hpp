/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** SafeQueue
*/

#pragma once
#include <mutex>
#include <queue>
#include <memory>
#include <iostream>

template <typename T>
class SafeQueue {
  public:
    SafeQueue() = default;
    SafeQueue(SafeQueue const& to_copy) = delete;
    SafeQueue(SafeQueue&& to_move) = default;

    ~SafeQueue() = default;

    SafeQueue& operator=(SafeQueue const& to_copy) = delete;

    void push(T value)
    {
        std::unique_lock<std::mutex> ul(*(this->m));

        queue.push(value);
    }
    /*
     * try to pop an element from the queue, and store it in value
     */
    bool tryPop(T& value)
    {
        std::unique_lock<std::mutex> ul(*(this->m), std::try_to_lock);

        if (!ul) {
#ifdef __DEBUG
        std::cout << "[DEBUG] couldnt lock the queue" << std::endl;
#endif
            return false;
        }
        if (this->queue.empty()) {
#ifdef __DEBUG
        std::cout << "[DEBUG] queue was empty" << std::endl;
#endif
            return false;
        }
#ifdef __DEBUG
        std::cout << "[DEBUG] elem in queue" << std::endl;
#endif
        value = this->queue.front();
        this->queue.pop();
        return true;
    }

  private:
    std::queue<T> queue;
    std::unique_ptr<std::mutex> m;
};
