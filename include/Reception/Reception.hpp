/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Pizza.hpp"

namespace Plazza
{
enum class Size
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
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
  private:
    float _TimeMultiplier;
    unsigned int _CooksPerKitchen;
    float _TimeStockRefill;
    std::chrono::high_resolution_clock::time_point _Time;
    std::string _Line;
    std::vector<std::vector<std::string>> _SplittedCmd;
    std::vector<PizzaCmd_t> _Commands;
    std::vector<std::pair<std::string, Pizza>> _Pizzas = {
        {"regina", Pizza::Regina},
        {"fantasia", Pizza::Fantasia},
        {"margarita", Pizza::Margarita},
        {"americana", Pizza::Americana},
    };

  public:
    Reception() = default;
    ~Reception() = default;
    int setValue(int ac, char** av);
    bool run();
    bool checkLine();
    std::vector<std::string> split(const std::string& s, char block);
    void makeCmd();
    PizzaCmd_t getCommandFromString(const std::vector<std::string>& com);
    bool cmdChecker(std::vector<std::string> command);
};
}

#endif /* !RECEPTION_HPP_ */
