/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Fork
*/

#include "MultiThread/Fork.hpp"


namespace Plazza
{
int Fork::plazzaFork()
{
    #ifdef __DEBUG
        std::cout << "[DEBUG] Forking" << std::endl;
    #endif
        int i = fork();
        if (i < 0) {
            throw(Plazza::PlazzaException("System Error: fork failed"));
        }
        return i;
    }
}
