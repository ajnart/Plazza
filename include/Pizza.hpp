/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Pizza
*/

#pragma once

#include <array>
#include <string>
#include <utility>

#include "FoodStock.hpp"

namespace Plazza {
static const std::array<std::pair<std::string, Ingredients_t>, 4> pizzas = {
    std::pair<std::string, Ingredients_t>(
        "Margarita", Ingredients_t{1, 1, 1, 0, 0, 0, 0, 0, 0}),
    std::pair<std::string, Ingredients_t>(
        "Regina", Ingredients_t{1, 1, 1, 1, 1, 0, 0, 0, 0}),
    std::pair<std::string, Ingredients_t>(
        "Americana", Ingredients_t{1, 1, 1, 0, 0, 1, 0, 0, 0}),
    std::pair<std::string, Ingredients_t>(
        "Fantasia", Ingredients_t{1, 1, 1, 0, 0, 0, 1, 1, 1})};
}
