/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#include "Reception.hpp"

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
Reception::Reception(params_t params)
{
    this->params = params;
    this->kitchens.push_back(KitchenIPC(params, 0));
#ifdef __DEBUG
        std::cout << "[DEBUG] Reception has been created" << std::endl;
#endif
}

std::vector<std::string> Reception::split(const std::string& s,
                                          char block) noexcept
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);

    while (std::getline(stream, token, block))
        tokens.push_back(token);
    return tokens;
}

void Reception::printStatus() noexcept
{
    int idx = 1;
    for (auto &i: kitchens) {
        std::cout << "Kitchen #" << idx << std::endl;
        idx++;
        i.printStatus();
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

    bool isIn = false;
    for (auto& i: {"S", "M", "L", "XL", "XXL"}) {
        if (i == parsed[1])
            isIn = true;
    }
    if (!isIn) {
        throw(PlazzaException("Unknown pizza size."));
    }
    try {
        command.type = parsed[0]; //PizzaType.at(parsed[0]);
        command.number = std::stoi(parsed[2]);
    } catch (std::out_of_range) {
        throw(PlazzaException("Unknown pizza type."));
    } catch (std::invalid_argument) {
        throw(PlazzaException("Invalid number of pizza"));
    }
    return command;
}

Action Reception::checkLine(std::string input) noexcept
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
        } catch (PlazzaException& e) {
            std::cout << e.what();
            Commands.clear();
            return Action::NONE;
        }
    }
    return Action::RUN;
}

bool Reception::assignToKitchen(PizzaCmd_t command)
{
    int best_index = 0;
    int best_nbr = this->kitchens[0].getPizzaNbr();

    for (int i = 0; i < this->kitchens.size(); i++) {
        int tmp = this->kitchens[0].getPizzaNbr();
        if (tmp < best_nbr) {
            best_nbr = tmp;
            best_index = i;
        }
    }
    return this->kitchens[best_nbr].addPizza(command.type);
}

void Reception::assignToNewKitchen(PizzaCmd_t command)
{
    this->kitchens.push_back(
        KitchenIPC(this->params, this->kitchens.size()));
    if (!this->kitchens.back().addPizza(command.type))
        throw std::logic_error("Fatal error: New Kitchen is full at creation");
}

void Reception::manageCommands()
{
    for (auto const& command: Commands) {
/* #ifdef __DEBUG */
/*         std::cout << "- "; */
/*         for (auto i = command.begin(); i != command.end(); ++i) */
/*             std::cout << *i << ' '; */
/* #endif */
        if (!this->assignToKitchen(command)) {
            this->assignToNewKitchen(command);
        }
    }
}

int Reception::run() noexcept
{
#ifdef __DEBUG
        std::cout << "[DEBUG] Reception is now running" << std::endl;
#endif
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
                this->manageCommands();
                Commands.clear();
                break;
            default:
                break;
        }
        // make algo with each elem of _Commands for (auto const &elem :
        // commands)
        std::cout << "\n$> ";
    }
    return 0;
}
} // namespace Plazza
