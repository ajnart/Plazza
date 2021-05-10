/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** KitchenInterface
*/

#include "MultiThread/KitchenIPC.hpp"

namespace Plazza
{
KitchenIPC::KitchenIPC(params_t params, int id) : kitchen(params, id)
{
    this->id = id;
    this->read.initPipe(id, NamedPipe::READ, true);
    this->write.initPipe(id, NamedPipe::WRITE, true);
    int pid = Fork::plazzaFork();
    if (pid == 0) {
        this->kitchen.run();
        exit(0);
    }
    this->read.openPipe();
    this->write.openPipe();
}
}
