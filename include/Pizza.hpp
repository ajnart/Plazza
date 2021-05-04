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
enum class Pizza
{
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

static const std::array<std::tuple<Pizza, Ingredients_t, int>, 4> pizzas = {
    std::tuple<Pizza, Ingredients_t, int>(
        Pizza::Margarita, Ingredients_t{.Does = 1, .Tomatoes = 1, .Gruyere = 1},
        1000),
    std::tuple<Pizza, Ingredients_t, int>(
        Pizza::Regina, Ingredients_t{1, 1, 1, 1, 1, 0, 0, 0, 0}, 2000),
    std::tuple<Pizza, Ingredients_t, int>(
        Pizza::Americana, Ingredients_t{1, 1, 1, 0, 0, 1, 0, 0, 0}, 2000),
    std::tuple<Pizza, Ingredients_t, int>(
        Pizza::Fantasia, Ingredients_t{1, 1, 1, 0, 0, 0, 1, 1, 1}, 4000)};
}
