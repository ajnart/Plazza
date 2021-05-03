/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** IReception
*/

#pragma once

struct Pizza {

}

namepace Plazza {
class Reception {
    public:
        /*
         * parse a input line into a list of pizzas
         */
        virtual std::vector<Pizza> getCommand(std::string) = 0;
        /*
         * sned a burger to the kitchen manager
         */
        virtual void askForPizza(std::vector<Pizza>);
    private:
        virtual void KitchenManager(const &Pizza)
}
}
