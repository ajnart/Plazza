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

class NamedPipe {
  public:
    enum Type_t
    {
        WRITE,
        READ
    };
    NamedPipe(int id, Type_t type)
    {
        this->type = type;
        this->fifo =
            "/tmp/fifo_" + std::string(type == READ ? "r_" : "w_") + std::to_string(id);
        this->openPipe();
    };
    NamedPipe(NamedPipe const& to_copy) = delete;
    NamedPipe(NamedPipe&& to_move) = default;

    ~NamedPipe() {
        this->write.close();
        this->read.close();
    }

    NamedPipe& operator=(NamedPipe const& to_copy) = delete;
    NamedPipe& operator=(NamedPipe && to_move) = default;

    void send(std::string msg)
    {
        if (!this->write.is_open()) {
            this->write << msg;
        }
    }
    std::string get()
    {
        std::string msg;
        if (this->read.is_open()) {
            getline(this->read, msg);
        }
        return msg;
    }
    bool tryGet(std::string& save)
    {
        std::string msg;
        int nbRead = 0;
        char c = 0;
        save.clear();
        do {
            nbRead = this->read.readsome(&c, 1);
            if (nbRead == 1) {
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
            this->read.open(this->fifo);
        } else {
            this->write.open(this->fifo);
        }
    }
};

