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
        Reception reception;
        reception.run();
        return 0;
    }
}    // namespace Plazza
