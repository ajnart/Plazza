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

    ~NamedPipe()
    {
        close(writefd);
        close(readfd);
        remove(this->fifo.data());
    }
    void initPipe(int id, Type_t type, bool parent)
    {
        std::cout << (parent ? "PARENT: " : "CHILD: ");
        std::cout << (type == WRITE ? "WRITE: \n" : "READ: \n");
        this->type = type;
        this->parent = parent;
        this->fifo = "fifo_" + std::to_string(id) +
                     std::string(parent ? (type == READ ? "0" : "1")
                                        : (type == READ ? "1" : "0"));
        if (parent) {
#ifdef __DEBUG
            std::cout << "Creating " << this->fifo << std::endl;
#endif
            remove(this->fifo.data());
            /* umask(0); */
            /* if (mknod(this->fifo.data(), 0666|S_IFIFO, 0) == -1) */
            /*     throw (Plazza::PlazzaException("pute")); */
            mkfifo(this->fifo.data(), 0667);
        }
    }
    void openPipe()
    {
        if (this->type == READ) {
            std::cout << "openning fifo for reading: " << this->fifo << "\n";

            readfd = open(fifo.data(), O_RDONLY);
            if (readfd < 0)
                throw(Plazza::PlazzaException("fuck read"));
            std::cout << "ok for " << (parent ? "PARENT" : "CHILD")
                      << " reading pipe\n";
        } else {
            std::cout << "openning fifo for writing: [" << this->fifo << "]\n";
            writefd = open(fifo.data(), O_WRONLY);
            if (writefd < 0)
                throw(Plazza::PlazzaException("fuck write"));
            std::cout << "ok for " << (parent ? "PARENT" : "CHILD")
                      << " writing pipe\n";
        }
    }

    NamedPipe& operator=(NamedPipe const& to_copy) = delete;
    NamedPipe& operator=(NamedPipe&& to_move) = default;

    void send(std::string msg)
    {
#ifdef __DEBUG
        std::cout << "sending " << msg << " to " << this->fifo << std::endl;
#endif
        // this->write.write(msg.data(), msg.size());
        /* write << msg; */
        write(this->writefd, msg.data(), msg.size());
    }
    std::string get()
    {
        char buf[64];
        read(readfd, buf, 64);
        /* getline(this->read, msg); */
#ifdef __DEBUG
        std::cout << "got [" << buf << "] from " << this->fifo << std::endl;
#endif
        return buf;
    }
    bool tryGet(std::string& save)
    {
#ifdef __DEBUG
        std::cout << "waiting for " << this->fifo << std::endl;
#endif
        std::string msg;
        int nbRead = 0;
        char c = 0;
        save.clear();
        do {
            read(readfd, &c, 1);
            /* nbRead = this->read.readsome(&c, 1); */
            if (nbRead == 1) {
#ifdef __DEBUG
                std::cout << "got something from " << this->fifo << std::endl;
#endif
                if (c == '\n') {
                    save = msg;
                    return true;
                } else {
                    msg.append(1, c);
                }
            }
        } while (c != 0);
        return false;
    }

  private:
    /* std::ofstream write; */
    /* std::ifstream read; */
    bool parent;
    int writefd;
    int readfd;
    Type_t type;
    std::string fifo;
};

