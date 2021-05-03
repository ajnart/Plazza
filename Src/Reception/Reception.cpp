/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#include "Reception.hpp"
#include <string.h>
#include "Help.hpp"
#include "Error.hpp"
#include <algorithm>

Reception::Reception()
{
}

Reception::~Reception()
{
}

bool Reception::run()
{
    std::cout << "$> ";
    while (getline(std::cin, _Line)) {
        std::cout << "\n$> ";
    }
    return true;
}


int Reception::setValue(int ac, char **av)
{
    std::string tmp(av[1]);
    if (ac == 2 && tmp.compare("-h") && tmp.compare("--help"))
        throw Help();
    else if (ac != 4)
        throw Error("Need 4 Arguments", "setValue");
    _TimeMultiplier = std::atof(av[1]);
    _CooksPerKitchen = std::atoi(av[2]);
    _TimeStockRefill = std::atof(av[3]) * 1000.0f;
    _Time = std::chrono::high_resolution_clock::now();
    if (_TimeMultiplier == 0.0f || !_CooksPerKitchen || !_TimeStockRefill)
        throw Error("bad Arguments", "setValue");
    std::cout << "the best pizzas under one roof\n";
}
