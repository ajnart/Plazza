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
#include <poll.h>
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

    ~NamedPipe()
    {
        close(writefd);
        close(readfd);
        remove(this->fifo.data());
    }
    void initPipe(int id, Type_t type, bool parent)
    {
        this->type = type;
        this->parent = parent;
        this->fifo = "fifo_" + std::to_string(id) +
                     std::string(parent ? (type == READ ? "0" : "1")
                                        : (type == READ ? "1" : "0"));
        if (parent) {
            remove(this->fifo.data());
            mkfifo(this->fifo.data(), 0667);
        }
    }
    void openPipe()
    {
        if (this->type == READ) {

            readfd = open(fifo.data(), O_RDONLY);
            if (readfd < 0)
                throw(Plazza::PlazzaException(""));
        } else {
            writefd = open(fifo.data(), O_WRONLY);
            if (writefd < 0)
                throw(Plazza::PlazzaException(""));
        }
    }

    NamedPipe& operator=(NamedPipe const& to_copy) = delete;
    NamedPipe& operator=(NamedPipe&& to_move) = default;

    void send(std::string msg)
    {
        write(this->writefd, msg.data(), msg.size());
    }
    std::string get()
    {
        char buf[10] = "\0\0\0\0\0\0\0\0\0";
        read(readfd, buf, 9);
        return buf;
    }
    bool tryGet(std::string& save)
    {
        struct pollfd ufd;
        ufd.fd = this->readfd;
        ufd.events = POLLIN;

        if (poll(&ufd, 1, 100) == 0) {
            return false;
        }
        save = this->get();
        return true;
    }

  private:
    bool parent;
    int writefd;
    int readfd;
    Type_t type;
    std::string fifo;
};

