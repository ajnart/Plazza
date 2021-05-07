/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Fork
*/

#pragma once
#include "PlazzaException.hpp"
#include <unistd.h>
#include <iostream>

class Fork {
  public:
    static int plazzaFork()
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
};
