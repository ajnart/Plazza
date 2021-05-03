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
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm>

Reception::Reception()
{
}

Reception::~Reception()
{
}

std::vector<std::string> Reception::split(const std::string &s, char block)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);

    while (std::getline(stream, token, block))
        tokens.push_back(token);
    return tokens;
}

bool Reception::checkLine()
{
    auto Split = split(_Line, ';');
    for (auto const &token:Split) {
        auto command = split(token, ' ');
        command.erase(std::remove_if(command.begin(), command.end(), [](const std::string &str) { return str.empty(); }), command.end());
        // error handler cmd
        // add cmd checker
        _SplittedCmd.push_back(command);
    }
    return true;
}

void Reception::makeCmd()
{
    for (auto const &command:_SplittedCmd)
        // fill a pizzaCmd struct with _SplittedCmd
    _SplittedCmd.clear();
}

bool Reception::run()
{
    std::cout << "$> ";
    while (getline(std::cin, _Line)) {
        checkLine();
        makeCmd();
        // make algo with each elem of _Commands for (auto const &elem : commands)
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
