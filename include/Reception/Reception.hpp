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

enum class Type
{
    Regina = 1,
    Margarita = 2,
    Americana = 4,
};

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

typedef struct pizzaCmd
{
    Type type;
    Size size;
    int number;
} PizzaCmd_t;

namespace Plazza
{
class Reception {
  private:
    float _TimeMultiplier;
    unsigned int _CooksPerKitchen;
    float _TimeStockRefill;
    std::chrono::high_resolution_clock::time_point _Time;
    std::string _Line;
    std::vector<std::vector<std::string>> _SplittedCmd;
    std::vector<PizzaCmd_t> _Commands;
    std::vector<std::pair<std::string, Type>> _Pizzas = {
        {"regina", Type::Regina},
        {"margarita", Type::Margarita},
        {"americana", Type::Americana},
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
