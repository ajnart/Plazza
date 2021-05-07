/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Fork
*/

#pragma once
#include "PlazzaException.hpp"
#include <unistd.h>

class Fork {
  public:
    static int fork()
    {
        int i = fork();
        if (i < 0) {
            throw(Plazza::PlazzaException("System Error: fork failed"));
        }
        return i;
    }
};
