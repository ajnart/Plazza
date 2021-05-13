/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** KitchenInterface
*/

#include "MultiThread/KitchenConnect.hpp"

namespace Plazza
{
KitchenConnect::KitchenConnect(params_t params, int id) : kitchen(params, id)
{
    this->id = id;
    this->read = NamedPipe(id, NamedPipe::READ, true);
    this->write = NamedPipe(id, NamedPipe::WRITE, true);
    int pid = Fork::plazzaFork();
    if (pid == 0) {
        this->kitchen.run();
        exit(0);
    }
    this->pid = pid;
    this->read->openPipe();
    this->write->openPipe();
}

bool KitchenConnect::IsActive()
{
    if (Fork::plazzaWait(this->pid) > 0)
        return false;
    return true;
}

void KitchenConnect::printStatus()
{
    this->write->send("STATUS\0");
    this->read->get();
}
int KitchenConnect::getPizzaNbr()
{
    this->write->send("PIZZANBR\0");
    return std::stoi(this->read->get());
}
void KitchenConnect::stop()
{
    this->write->send("STOP");
    Fork::plazzaWait(pid);
}
/*
 *->send a pizza to a kitchen, return weither the op succeded or not
 */
bool KitchenConnect::addPizza(std::string pizzaType)
{
    std::cout << "ébite" << std::endl;
    this->write->send(pizzaType + "\0");
    return this->read->get() == "TRUE" ? true : false;
}
}
