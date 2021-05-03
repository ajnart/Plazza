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

class Reception {
    private:
        float _TimeMultiplier;
        unsigned int _CooksPerKitchen;
        float _TimeStockRefill;
        std::chrono::high_resolution_clock::time_point _Time;
        std::string _Line;
    public:
        Reception();
        ~Reception();
        int setValue(int ac, char **av);
        bool run();
        bool checkLine();
};

#endif /* !RECEPTION_HPP_ */
