/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>

enum class Type {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
};

enum class Size {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
};

typedef struct pizzaCmd {
    Type type;
    Size size;
    int number;
} PizzaCmd_t;

class Reception {
    private:
        float _TimeMultiplier;
        unsigned int _CooksPerKitchen;
        float _TimeStockRefill;
        std::chrono::high_resolution_clock::time_point _Time;
        std::string _Line;
        std::vector<std::vector<std::string>> _SplittedCmd;
        std::vector<PizzaCmd_t> _Commands;
        std::vector<std::pair<std::string, Type>> pizzas = {
            {"regina", Type::Regina},
            {"margarita", Type::Margarita},
            {"americana", Type::Americana},
        };
    public:
        Reception();
        ~Reception();
        int setValue(int ac, char **av);
        bool run();
        bool checkLine();
        std::vector<std::string> split(const std::string &s, char block);
        void makeCmd();
};

#endif /* !RECEPTION_HPP_ */
