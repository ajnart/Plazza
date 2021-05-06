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
    Reception reception(params.multiplier, params.chefs_nbr,
                        params.stock_refill_time);
    return reception.run();
    /* Plazza::Kitchen k{15, 2000, 2}; */
    /* k.status(); */
    /* k.stop(); */
    // Reception reception;
    // reception.run();
    /* return 0; */
}
} // namespace Plazza
