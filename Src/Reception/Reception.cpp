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

std::vector<std::string> Reception::split(const std::string &s, char block)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);

    while (std::getline(stream, token, block))
        tokens.push_back(token);
    return tokens;
}

bool Reception::cmdChecker(std::vector<std::string> command)
{
    for (int i = 0; i < 3; ++i) {
        if (i == 0) {
            for (int j = 0; j < 3; ++j) {
                if (command[i] == _Pizzas[j].first)
                    return true;
            } throw("bad type", "cmdChecker");
        } else if (i == 1) {
            if (command[i] != "S" && command[i] != "M" && command[i] != "L" && command[i] != "XL" && command[i] != "XXL")
                throw("bad size", "cmdChecker");
            return true;
        } else {
            if (std::regex_match(command[i], std::regex("x[0-9]*")))
                return true;
            throw("bad pizza's number", "cmdChecker");
        }
    }
}

bool Reception::checkLine()
{
    auto Split = split(_Line, ';');
    for (auto const &token:Split) {
        auto command = split(token, ' ');
        command.erase(std::remove_if(command.begin(), command.end(), [](const std::string &str) { return str.empty(); }), command.end());
        if (command.size() != 3)
            throw("Error bad size", "checkLine");
        cmdChecker(command);
        _SplittedCmd.push_back(command);
    }
    return true;
}

void Reception::makeCmd()
{
    for (auto const &command:_SplittedCmd) {
        auto newCommand = PizzaCmd_t();
        for (int i = 0; i < 3; ++i) {
            if (i == 0) {
                for (auto const &elem:_Pizzas) {
                    if (elem.first == command[0])
                        newCommand.type = elem.second;
                }
            } else if (i == 1) {
                for (auto const &elem:pizzaSizes) {
                    if (elem.first == command[1])
                        newCommand.size = elem.second;
                }
            } else
                newCommand.number = atoi(&(command[i].c_str()[1]));
        }
        _Commands.push_back(newCommand);
    }
    _SplittedCmd.clear();
}

bool Reception::run()
{
    std::cout << "$> ";
    while (getline(std::cin, _Line)) {
        try {
            checkLine();
        } catch (Error &e) {
            std::cout << e.getWhat() << '\n';
        }
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
