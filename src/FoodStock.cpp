/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** FoodStuck
*/

#include "FoodStock.hpp"

namespace Plazza
{
FoodStock::FoodStock()
{
    return;
}

bool FoodStock::tryConsumeIngredients(const Ingredients_t& i)
{
    return true;
}

const Ingredients_t& FoodStock::getIngredients()
{
    return Ingredients;
}

void FoodStock::refill()
{
    Ingredients.Does += 1;
    Ingredients.Tomatoes += 1;
    Ingredients.Gruyere += 1;
    Ingredients.Ham += 1;
    Ingredients.Mushrooms += 1;
    Ingredients.Steak += 1;
    Ingredients.Eggplant += 1;
    Ingredients.GoatCheese += 1;
    Ingredients.ChiefLove += 1;
    return;
}
}
