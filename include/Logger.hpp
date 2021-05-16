/*
** EPITECH PROJECT, 2021
** Plazza [SSH: elitebook]
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <sstream>

constexpr bool DEBUG_PRINTS = true;

class Logger {
    public:
        Logger() = default;
        ~Logger() = default;
        static void log(const std::string &message)
        {
            std::ofstream out("logs.log", std::fstream::app);
            out << "[I] " << message << std::endl;
            std::cout << message << std::endl;
            out.close();
        }
        static void debuglog(const std::string &message)
        {
            std::ofstream out("logs.log", std::fstream::app);
            out << "[D] " << message << std::endl;
            std::cout << message << std::endl;
            out.close();
        }
        static void logfile(const std::string &message) {
            std::ofstream out("logs.log", std::fstream::app);
            out << "[I] " << message << std::endl;
            out.close();
        }
        static void logIPC(const std::string& message)
        {
            std::ofstream out("IPC.log", std::fstream::app);
            out << "[IPC] " << message << std::endl;
            std::cout << message << std::endl;
            out.close();
        }
};

#endif /* !LOGGER_HPP_ */
