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
#include <vector>

namespace Plazza
{
static const std::vector<std::pair<std::string, Pizza>> Pizzas = {
    {"regina", Pizza::Regina},
    {"fantasia", Pizza::Fantasia},
    {"margarita", Pizza::Margarita},
    {"americana", Pizza::Americana},
};
enum class Size
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
};

enum Action
{
    NONE = 0,
    HELP,
    STATUS,
    EXIT,
    RUN,
};

const std::vector<std::pair<std::string, Size>> pizzaSizes = {
    {"S", Size::S},
    {"M", Size::M},
    {"L", Size::L},
    {"XL", Size::XL},
};

struct PizzaCmd_t
{
    Pizza type;
    Size size;
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
    void makeCmd();
    /*
     * parse the string str and return a command structure.
     * throw if any error happend
     */
    PizzaCmd_t getCommandFromString(const std::string str);
    bool cmdChecker(std::vector<std::string> command);
    std::chrono::high_resolution_clock::time_point Time;

    std::vector<PizzaCmd_t> Commands;
    std::vector<Kitchen> kitchens;
};

}

#endif /* !RECEPTION_HPP_ */
