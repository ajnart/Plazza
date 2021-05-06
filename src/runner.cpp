/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** plazza
*/

#include "ArgParse.hpp"
#include "Reception/Reception.hpp"

namespace Plazza
{
    int plazza(params_t params)
    {
        Plazza::Kitchen k{params.multiplier, params.chefs_nbr, params.stock_refill_time};
        k.status();
        k.Cooks[0].bake(5000);
        k.Cooks[1].bake(1000);
        k.Cooks[5].bake(5000);
        k.status();
        Reception reception;
        reception.run();
        k.status();
        k.stop();
        return 0;
    }
}    // namespace Plazza
