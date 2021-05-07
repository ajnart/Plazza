/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** SafeQueue
*/

#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>

template <typename T>
class SafeQueue {
  public:
    SafeQueue() : m(std::make_unique<std::mutex>()){
        std::cout << m.get() << std::endl;
    };
    SafeQueue(SafeQueue const& to_copy) = delete;
    SafeQueue(SafeQueue&& to_move) :
        queue(std::move(to_move.queue)), m(std::move(to_move.m)){};

    ~SafeQueue() = default;

    SafeQueue& operator=(SafeQueue const& to_copy) = delete;
    SafeQueue& operator=(SafeQueue&& to_move)
    {
        this->queue = std::move(to_move.queue);
        this->m = std::move(to_move.m);
    }

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
        std::cout << m.get() << std::endl;
        if (this->m.get() == nullptr)
            std::cout << "bite" << std::endl;
        std::unique_lock<std::mutex> lock(*(this->m), std::defer_lock);

        if (!lock.try_lock()) {
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
