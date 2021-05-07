/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "PlazzaException.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <tuple>
#include <unistd.h>

namespace Plazza
{
Kitchen::Kitchen(params_t params, int id) :
    write(id, NamedPipe::WRITE, false),
    read(id, NamedPipe::READ, false),
    cookNb(params.chefs_nbr),
    refillTime(params.stock_refill_time),
    CookTimeMultiplier(params.multiplier),
    Cooks(params.chefs_nbr)
{
    this->id = id;
#ifdef __DEBUG
    std::cout << "[DEBUG] kitchen " << id << " have been created!" << std::endl;
#endif
}

Kitchen::~Kitchen()
{}

void Kitchen::status(void) noexcept
{
    Plazza::Ingredients_t i = this->Stock.getIngredients();
    std::cout << "Ingredients:\n"
              << "D:" << i.Does << "\tT:" << i.Tomatoes << "\tG:" << i.Gruyere
              << std::endl
              << "H:" << i.Ham << "\tM:" << i.Mushrooms << "\tS:" << i.Steak
              << std::endl
              << "E:" << i.Eggplant << "\tGC:" << i.GoatCheese
              << "\tCL:" << i.ChiefLove << std::endl;

    for (auto& i: this->Cooks)
        std::cout << (i.isBusy() ? "\033[31m •\033[0m" : "\033[32m •\033[0m");
    std::cout << std::endl;
}

void Kitchen::getPizzaNbr() noexcept
{
    this->write.send(std::to_string(this->pizzaNb));
}

/* bool Kitchen::addPizza(std::string pizzaName) noexcept */
/* { */
/*     Pizza pizza = PizzaType.at(pizzaName); */
/*     if (this->pizzaNb >= this->cookNb) */
/*         return false; */
/*     this->queue.push(pizza); */
/*     this->pizzaNb += 1; */
/*     return true; */
/* } */

using attr = std::tuple<Pizza, Ingredients_t, int>;

bool Kitchen::CookManager(attr attrs)
{
    for (auto cook = this->Cooks.begin(); cook != this->Cooks.end(); cook++) {
        if (!cook->isBusy() &&
            this->Stock.tryConsumeIngredients(std::get<1>(attrs))) {
            cook->bake(std::get<2>(attrs) * this->CookTimeMultiplier);
            this->pizzaNb -= 1;
            return true;
        }
    }
    return false;
}

attr getPizzaAttributes(const Pizza& pizza)
{
    auto attributes =
        std::find_if(pizzas.begin(), pizzas.end(), [=](auto item) {
            return std::get<0>(item) == pizza;
        });
    if (attributes not_eq pizzas.end()) {
        return *attributes;
    }
    throw(PlazzaException("Unknown Pizza type."));
}

void Kitchen::handlePizza(const std::string& name)
{
    if (this->pizzaNb > this->cookNb) {
        this->write.send("FALSE\n");
        return;
    }
    Pizza pizza = PizzaType.at(name);
    this->queue.push(pizza);
     this->pizzaNb += 1;
    attr attributes = getPizzaAttributes(pizza);
}

void Kitchen::run()
{
    std::string commandLine;
#ifdef __DEBUG
    std::cout << "[DEBUG] kitchen " << id << " is running!" << std::endl;
#endif

    while (1) {
        this->tryRefill();
        if (this->read.tryGet(commandLine)) {
#ifdef __DEBUG
    std::cout << "[DEBUG] kitchen " << id << ": flushed command!" << std::endl;
#endif
            if (commandLine == "STATUS")
                this->status();
            else if (commandLine == "PIZZANBR")
                this->getPizzaNbr();
            else if (commandLine == "STOP")
                return;
            else
                this->handlePizza(commandLine);
            Pizza tmp = this->queue.front();
            attr attributes = getPizzaAttributes(tmp);
            if (this->CookManager(attributes)) {
                this->queue.pop();
            }

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

bool Kitchen::tryRefill() noexcept
{
    static auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) >=
        std::chrono::milliseconds(this->refillTime)) {
/* #ifdef __DEBUG */
/*         std::cout << "[DEBUG] Refilling ingredients for kitchen" << std::endl; */
/* #endif */
        t1 = std::chrono::high_resolution_clock::now();
        this->Stock.refill();
        return true;
    }
    return false;
}

}
