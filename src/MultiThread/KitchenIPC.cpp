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
void KitchenIPC::printStatus()
{
    this->write.send("STATUS\0");
    this->read.get();
}
int KitchenIPC::getPizzaNbr()
{
    this->write.send("PIZZANBR\0");
    return std::stoi(this->read.get());
}
void KitchenIPC::stop()
{
    this->write.send("STOP");
}
/*
 * send a pizza to a kitchen, return weither the op succeded or not
 */
bool KitchenIPC::addPizza(std::string pizzaType)
{
    this->write.send(pizzaType + "\0");
    return this->read.get() == "TRUE" ? true : false;
}
}
