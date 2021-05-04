/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include "FoodStock.hpp"

namespace Plazza {
class Kitchen {
    public:
        bool isKitchenFull();
        int getPizzaNb();
        /*
         * return occupancy of the cooks, and stock of ingredients
         */
        /* smth */void status();
    private:
        int cook_nb = 0;
        int pizza_nb = 0;
        FoodStock stock;
};
}
