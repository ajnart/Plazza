/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** NamedPipe
*/

#include "MultiThread/NamedPipe.hpp"
NamedPipe::~NamedPipe()
{
    close(writefd);
    close(readfd);
    remove(this->fifo.data());
}
void NamedPipe::initPipe(int id, Type_t type, bool parent)
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
void NamedPipe::openPipe()
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
void NamedPipe::send(std::string msg)
{
    write(this->writefd, msg.data(), msg.size());
}
std::string NamedPipe::get()
{
    char buf[10] = "\0\0\0\0\0\0\0\0\0";
    read(readfd, buf, 9);
    return buf;
}
bool NamedPipe::tryGet(std::string& save)
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
