/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** KitchenInterface
*/

/* #include "KitchenInterface.hpp" */
/* #include "MultiThread/Process.hpp" */

/* namespace Plazza */
/* { */
/* KitchenIntreface::KitchenIntreface(params_t params) */
/* { */
/*     Fork process; */

/*     if (!process.isParent()) { */
/*         //start kitchen */
/*         exit(0); */
/*     } */
/*     this->wfd = process.getWrite(); */
/*     this->rfd = process.getRead(); */
/* } */

/* } */

#include "MultiThread/KitchenIPC.hpp"

namespace Plazza
{
KitchenIPC::KitchenIPC(params_t params, int id) : kitchen(params, id)
{
    /* read(id, NamedPipe::READ, true), */
        /* write(id, NamedPipe::WRITE, true) */
    #ifdef __DEBUG
        std::cout << "[DEBUG] Creating a Kitchen IPC with id " << id
        << std::endl;
    #endif
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
        this->write.send("STATUS");
}

int KitchenIPC::getPizzaNbr()
{
        this->write.send("PIZZANBR");
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
    this->write.send(pizzaType);
    return this->read.get() == "TRUE" ? true : false;
}
}
