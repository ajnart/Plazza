/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#include "Reception/Reception.hpp"

#include <string.h>

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "PlazzaException.hpp"

namespace Plazza
{
std::vector<std::string> Reception::split(const std::string& s, char block)
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
            }
            throw(PlazzaException("Invalid pizza type."));
        } else if (i == 1) {
            if (command[i] != "S" && command[i] != "M" && command[i] != "L" &&
                command[i] != "XL" && command[i] != "XXL")
                throw(PlazzaException(
                    "Invalid pizza size. Valid size are [S/M/L/XL/XXL]"));
            return true;
        } else {
            if (std::regex_match(command[i], std::regex("x[0-9]*")))
                return true;
            throw(PlazzaException("invalid pizza's number"));
        }
    }
    return false;
}

bool Reception::checkLine()
{
    auto Split = split(_Line, ';');
    for (auto const& token: Split) {
        auto command = split(token, ' ');
        command.erase(std::remove_if(command.begin(), command.end(),
                                     [](const std::string& str) {
                                         return str.empty();
                                     }),
                      command.end());
        if (command.size() != 3)
            throw(PlazzaException("Invalid size"));
        cmdChecker(command);
        _SplittedCmd.push_back(command);
    }
    return true;
}

void Reception::makeCmd()
{
    for (auto const& command: _SplittedCmd) {
        auto newCommand = PizzaCmd_t();
        for (int i = 0; i < 3; ++i) {
            if (i == 0) {
                for (auto const& elem: _Pizzas) {
                    if (elem.first == command[0])
                        newCommand.type = elem.second;
                }
            } else if (i == 1) {
                for (auto const& elem: pizzaSizes) {
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
        } catch (PlazzaException& e) {
            std::cout << e.what() << '\n';
        }
        makeCmd();
        // make algo with each elem of _Commands for (auto const &elem :
        // commands)
        std::cout << "\n$> ";
    }
    return true;
}
} // namespace Plazza
