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
#include <tuple>
#include <vector>

#include "ArgParse.hpp"
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
                if (command[i] == Pizzas[j].first)
                    return true;
            }
            throw(PlazzaException("Invalid pizza type."));
        } else if (i == 1) {
            if (command[i] != "S" && command[i] != "M" && command[i] != "L" &&
                command[i] != "XL" && command[i] != "XXL")
                throw(PlazzaException(
                    "Invalid pizza size. Valid sizes are [S/M/L/XL/XXL]"));
            return true;
        } else {
            if (std::regex_match(command[i], std::regex("x[0-9]*")))
                return true;
            throw(PlazzaException("Invalid number of pizzas."));
        }
    }
    return false;
}

void Reception::printStatus()
{
    for (auto& i: kitchens) {
        i.status();
    }
}

static void printHelp()
{
    std::cout << "Pizza ordering MUST respect the following grammar:"
              << std::endl
              << "S := TYPE SIZE NUMBER[; TYPE SIZE NUMBER]* TYPE :"
              << std::endl
              << "Type\t= [a..zA..Z] + SIZE :" << std::endl
              << "Size\t= S | M | L | XL | XXL NUMBER :" << std::endl
              << "Number\t= x[1..9][0..9] *" << std::endl
              << "Ordering example which is grammatically valid:" << std::endl
              << "regina XXL x2; fantasia M x3;margarita S x1\"" << std::endl;
}

PizzaCmd_t Reception::getCommandFromString(const std::string str)
{
    std::vector<std::string> parsed = this->split(str, ' ');
    PizzaCmd_t command;

    if (parsed.size() != 3)
        throw(PlazzaException("Invalid command. Type 'help' to view help."));
}

Action Reception::checkLine(std::string input)
{
    if (input == "help")
        return Action::HELP;
    if (input == "status")
        return Action::STATUS;
    if (input == "exit")
        return Action::EXIT;
    auto commands = split(input, ';');
    for (auto const& token: commands) {
        try {
            Commands.push_back(getCommandFromString(token));
        }
        /*
        auto command = split(token, ' ');
        command.erase(std::remove_if(command.begin(), command.end(),
                                     [](const std::string& str) {
                                         return str.empty();
                                     }),
                      command.end());
        if (command.size() != 3)
            throw(PlazzaException(
                "Invalid command. Type 'help' to view help."));
        cmdChecker(command);
        SplittedCmd.push_back(command);*/
    }
    return Action::RUN;
}

void Reception::makeCmd()
{
    for (auto const& command: _SplittedCmd) {
#ifdef __DEBUG
        std::cout << "- ";
        for (auto i = command.begin(); i != command.end(); ++i)
            std::cout << *i << ' ';
#endif
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
                newCommand.number = std::stoi(&(command[i].c_str()[1]));
        }
        _Commands.push_back(newCommand);
    }
    _SplittedCmd.clear();
}

int Reception::run()
{
    std::string line;
    Action action = Action::NONE;
    std::cout << "$> ";
    while (getline(std::cin, line)) {
        try {
            action = this->checkLine(line);
        } catch (PlazzaException& e) {
            std::cout << e.what() << std::endl;
        }
        switch (action) {
            case Action::EXIT:
                return 0;
            case Action::HELP:
                printHelp();
                break;
            case Action::STATUS:
                this->printStatus();
                break;
            case Action::RUN:
                this->makeCmd(line);
                break;
            default:
                break;
        }
        makeCmd();
        // make algo with each elem of _Commands for (auto const &elem :
        // commands)
        std::cout << "\n$> ";
    }
    return true;
}
} // namespace Plazza
