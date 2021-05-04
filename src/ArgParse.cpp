/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** ArgParse
*/

#include "ArgParse.hpp"

#include <iostream>

#include "PlazzaException.hpp"

bool ArgParse::isArgsNumberCorrect(int ac) noexcept
{
    if (ac == 4)
        return true;
    std::cerr << "Wrong number of arguments. Do ./plazza -h to learn about the program." << std::endl;
    return false;
}

params_t ArgParse::ParseArgs(char** args)
{
    params_t params;
    
    try {
        params.multiplier = std::stof(args[1]);
        params.chefs_nbr = std::stoi(args[2]);
        params.stock_refill_time = std::stof(args[3]);
    } catch (std::invalid_argument) {
        throw Plazza::PlazzaException("Invalid arguments. Do ./plazza -h to learn about argument formats.");
    }
    return params;
}

void ArgParse::printHelp() noexcept
{
    std::cout << "bite";
}
