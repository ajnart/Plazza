/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** FoodStock
*/

#pragma once

#include <mutex>

namespace Plazza
{
struct Ingredients_t
{
    int Does = 0;
    int Tomatoes = 0;
    int Gruyere = 0;
    int Ham = 0;
    int Mushrooms = 0;
    int Steak = 0;
    int Eggplant = 0;
    int GoatCheese = 0;
    int ChiefLove = 0;
};

class FoodStock {
  public:
    /*
     * fill Ingredients with 5 unit for each Ingredients
     */
    FoodStock();
    FoodStock(FoodStock const& to_copy) = delete;
    FoodStock(FoodStock&& to_move) = delete;

    ~FoodStock() = default;

    FoodStock& operator=(FoodStock const& to_copy) = delete;

    /*
     * remove i from Ingredients. if there is not enough Ingredients,
     * return false, else, return true
     */
    bool getIngredients(const Ingredients_t& i);
    /*
     * refill every ingredients
     */
    void refill();

  private:
    Ingredients_t Ingredients;
    std::mutex m;
};
}
