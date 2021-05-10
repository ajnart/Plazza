/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** NamedPipes
*/

#pragma once

#include "PlazzaException.hpp"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

class NamedPipe {
  public:
    enum Type_t
    {
        WRITE,
        READ
    };
    NamedPipe() = default;
    NamedPipe(NamedPipe const& to_copy) = delete;
    NamedPipe(NamedPipe&& to_move) = default;

    ~NamedPipe();

    void initPipe(int id, Type_t type, bool parent);
    void openPipe();

    NamedPipe& operator=(NamedPipe const& to_copy) = delete;
    NamedPipe& operator=(NamedPipe&& to_move) = default;

    void send(std::string msg);
    std::string get();
    bool tryGet(std::string& save);

  private:
    /* std::ofstream write; */
    /* std::ifstream read; */
    bool parent;
    int writefd;
    int readfd;
    Type_t type;
    std::string fifo;
};

