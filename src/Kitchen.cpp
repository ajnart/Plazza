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
Kitchen::Kitchen(float multiplier, unsigned int chefs_nbr, unsigned int stock_refill_time) :
    cookNb(chefs_nbr),
    refillTime(stock_refill_time),
    CookTimeMultiplier(multiplier),
    t(&Kitchen::run, this),
    Cooks(chefs_nbr)
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

int Kitchen::getPizzaNbr() noexcept
{
    return this->pizzaNb;
}

bool Kitchen::addPizza(const Pizza& pizza) noexcept
{
    if (this->pizzaNb >= this->cookNb * 2)
        return false;
    this->Queue.push(pizza);
    this->pizzaNb += 1;
    return true;
}

using attr = std::tuple<Pizza, Ingredients_t, int>;

bool Kitchen::CookManager(attr attrs)
{
    for (auto cook = this->Cooks.begin(); cook != this->Cooks.end(); cook++) {
        if (!cook->isBusy() &&
            this->Stock.tryConsumeIngredients(std::get<1>(attrs))) {
            cook->bake(std::get<2>(attrs) * this->CookTimeMultiplier);
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

void Kitchen::run()
{
    Pizza pizza;
    attr attributes = getPizzaAttributes(Pizza::None);
    while (this->running) {
        this->tryRefill();
        if (std::get<0>(attributes) == Pizza::None) {
            if (this->Queue.tryPop(pizza)) {
                attributes = getPizzaAttributes(pizza);
                if (this->CookManager(attributes)) {
                    attributes = getPizzaAttributes(Pizza::None);
                }
            }
        } else {
            if (this->CookManager(attributes)) {
                attributes = getPizzaAttributes(Pizza::None);
            }
        }
    }
}

bool Kitchen::tryRefill() noexcept
{
    static auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) >=
        std::chrono::milliseconds(this->refillTime)) {
#ifdef __DEBUG
        std::cout << "[DEBUG] Refilling ingredients for kitchen" << std::endl;
#endif
        t1 = std::chrono::high_resolution_clock::now();
        this->Stock.refill();
        return true;
    }
    return false;
}

}
