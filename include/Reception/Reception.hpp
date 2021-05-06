/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Kitchen.hpp"
#include "Pizza.hpp"
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <map>

namespace Plazza
{
static const std::map<std::string, Pizza> PizzaType = {
    {"regina", Pizza::Regina},
    {"fantasia", Pizza::Fantasia},
    {"margarita", Pizza::Margarita},
    {"americana", Pizza::Americana},
};

enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

enum Action
{
    NONE = 0,
    HELP,
    STATUS,
    EXIT,
    RUN,
};

struct PizzaCmd_t
{
    Pizza type;
    int number;
};

class Reception {
  public:
    Reception() = default;
    Reception(Reception const& to_copy) = default;
    Reception(Reception&& to_move) = default;

    ~Reception() = default;

    Reception& operator=(Reception const& to_copy) = default;

    /*
     * entrypoint of the Reception
     */
    int run() noexcept;

  private:
    /*
     * read the input, and return the action to execute
     */
    Action checkLine(std::string command) noexcept;
    /*
     * print the status of kitchens
     */
    void printStatus() noexcept;

    int setValue(int ac, char** av);
    /*
     * split the string s according to the delimitor, into a vector of string
     */
    std::vector<std::string> split(const std::string& s,
                                   char delimitor) noexcept;
    /*
     * pop every commands from Commands, and send them to kicthens
     */
    void manageCommands();
    /*
     * parse the string str and return a command structure.
     * throw if any error happend
     */
    PizzaCmd_t getCommandFromString(const std::string str);

    std::vector<PizzaCmd_t> Commands;
    std::vector<Kitchen> kitchens;
};

}

#endif /* !RECEPTION_HPP_ */
