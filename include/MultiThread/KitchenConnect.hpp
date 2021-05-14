/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** KitchenInterface
*/

#pragma once
#include "ArgParse.hpp"
#include "Kitchen.hpp"
#include "MultiThread/Fork.hpp"
#include "MultiThread/NamedPipe.hpp"
#include "Pizza.hpp"
#include <optional>

namespace Plazza
{
class KitchenConnect {
  public:
    KitchenConnect(params_t params, int id);
    KitchenConnect(KitchenConnect const& to_copy) = delete;
    KitchenConnect(KitchenConnect&& to_move) = delete;

    ~KitchenConnect() {
        std::cout << "!!!!! KITCHENCONNECT " << id << " DESTROYED !!!!!!\n";
        remove(("fifo" + std::to_string(pid) + "0").c_str());
        remove(("fifo" + std::to_string(pid) + "1").c_str());
    }

    KitchenConnect& operator=(KitchenConnect const& to_copy) = delete;
    KitchenConnect& operator=(KitchenConnect&& to_move) = delete;

    void printStatus();

    int getPizzaNbr();

    void stop();

    bool addPizza(std::string pizzaType);
    bool IsActive();
    int id;
  private:
    int pid;
    /* Kitchen kitchen; */
    NamedPipe write;
    NamedPipe read;
};
}
