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

    void printStatus()
    {
        this->write.send("STATUS\0");
        this->read.get();
    }
    int getPizzaNbr()
    {
        this->write.send("PIZZANBR\0");
        return std::stoi(this->read.get());
    }
    void stop()
    {
        this->write.send("STOP");
    }
    /*
     * send a pizza to a kitchen, return weither the op succeded or not
     */
    bool addPizza(std::string pizzaType)
    {
        this->write.send(pizzaType + "\0");
        return this->read.get() == "TRUE" ? true : false;
    }

  private:
    Kitchen kitchen;
    NamedPipe write;
    NamedPipe read;
    int id;
};
}
