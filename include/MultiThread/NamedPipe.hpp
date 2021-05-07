/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** NamedPipes
*/

#pragma once

#include <fcntl.h>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <iostream>

class NamedPipe {
  public:
    enum Type_t
    {
        WRITE,
        READ
    };
    NamedPipe(int id, Type_t type, bool parent)
    {
        this->type = type;
        this->fifo =
            "/tmp/fifo_" + std::to_string(id) + std::string(parent ? (type == READ ? "0" : "1") : (type == READ ? "1" : "0"));
        this->openPipe();
    };
    NamedPipe(NamedPipe const& to_copy) = delete;
    NamedPipe(NamedPipe&& to_move) = default;

    ~NamedPipe() {
        this->write.close();
        this->read.close();
        remove(this->fifo.data());
    }

    NamedPipe& operator=(NamedPipe const& to_copy) = delete;
    NamedPipe& operator=(NamedPipe && to_move) = default;

    void send(std::string msg)
    {
#ifdef __DEBUG
        std::cout << "sending " << msg << " to " << this->fifo << std::endl;
#endif
        if (!this->write.is_open()) {
            this->write.write(msg.data(), msg.size());
        }
    }
    std::string get()
    {
        std::string msg;
        if (this->read.is_open()) {
            getline(this->read, msg);
        }
#ifdef __DEBUG
        std::cout << "got " << msg << " from " << this->fifo << std::endl;
#endif
        return msg;
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
            nbRead = this->read.readsome(&c, 1);
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
    std::ofstream write;
    std::ifstream read;
    Type_t type;
    std::string fifo;
    void openPipe()
    {
        mkfifo(this->fifo.data(), 0667);
        if (this->type == READ) {
            std::cout << "openning fifo for reading: " << this->fifo << "\n";
            this->read.open(this->fifo, std::ifstream::out);
        } else {
            std::cout << "openning fifo for writing: " << this->fifo << "\n";
            this->write.open(this->fifo, std::ifstream::in);
        }
    }
};

