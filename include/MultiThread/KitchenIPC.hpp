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

namespace Plazza
{
class KitchenIPC {
  public:
    KitchenIPC(params_t params, int id);
    KitchenIPC(KitchenIPC const& to_copy) = delete;
    KitchenIPC(KitchenIPC&& to_move) = default;

    ~KitchenIPC() = default;

    KitchenIPC& operator=(KitchenIPC const& to_copy) = delete;
    KitchenIPC& operator=(KitchenIPC&& to_move) = delete;

    void printStatus();

    int getPizzaNbr();

    void stop();

    bool addPizza(std::string pizzaType);

  private:
    Kitchen kitchen;
    NamedPipe write;
    NamedPipe read;
    int id;
};
}
