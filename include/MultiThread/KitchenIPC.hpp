/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** KitchenInterface
*/

#pragma once
#include "ArgParse.hpp"
#include "Kitchen.hpp"
#include "MultiThread/NamedPipe.hpp"
#include "Pizza.hpp"
#include "MultiThread/Fork.hpp"

namespace Plazza{
class KitchenIPC {
  public:
    KitchenIPC(params_t params, int id)
    : write(id, NamedPipe::WRITE, true),
      read(id, NamedPipe::READ, true),
      kitchen(params, id)
    {
#ifdef __DEBUG
        std::cout << "[DEBUG] Creating a Kitchen IPC with id " << id << std::endl;
#endif
        this->id = id;
        int pid = Fork::plazzaFork();
        if (pid == 0) {
            this->kitchen.run();
            exit(0);
        }
    }
    KitchenIPC(KitchenIPC const& to_copy) = delete;
    KitchenIPC(KitchenIPC&& to_move) = default;

    ~KitchenIPC() = default;

    KitchenIPC& operator=(KitchenIPC const& to_copy) = delete;
    KitchenIPC& operator=(KitchenIPC && to_move) = delete;

    void printStatus() {
        this->write.send("STATUS\n");
    }
    int getPizzaNbr() {
        this->write.send("PIZZANBR\n");
        return std::stoi(this->read.get());
    }
    void stop() {
        this->write.send("STOP\n");
    }
    /*
     * send a pizza to a kitchen, return weither the op succeded or not
     */
    bool addPizza(std::string pizzaType) {
        this->write.send(pizzaType + "\n");
        return this->read.get() == "TRUE" ? true : false;
    }

  private:
    NamedPipe write;
    NamedPipe read;
    Kitchen kitchen;
    int id;
};
}
