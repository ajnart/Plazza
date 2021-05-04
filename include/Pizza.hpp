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

namespace Plazza
{
static const std::array<std::tuple<std::string, Ingredients_t, int>, 4> pizzas =
    {std::tuple<std::string, Ingredients_t, int>(
         "Margarita", Ingredients_t{.Does = 1, .Tomatoes = 1, .Gruyere = 1},
         1000),
     std::tuple<std::string, Ingredients_t, int>(
         "Regina", Ingredients_t{1, 1, 1, 1, 1, 0, 0, 0, 0}, 2000),
     std::tuple<std::string, Ingredients_t, int>(
         "Americana", Ingredients_t{1, 1, 1, 0, 0, 1, 0, 0, 0}, 2000),
     std::tuple<std::string, Ingredients_t, int>(
         "Fantasia", Ingredients_t{1, 1, 1, 0, 0, 0, 1, 1, 1}, 4000)};
}
