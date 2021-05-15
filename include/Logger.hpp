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

class Logger {
    public:
        Logger() = default;
        ~Logger() = default;
        static void log(std::string message)
        {
            std::ofstream out("logs.log", std::fstream::app);
            out << "[I] " << message << std::endl;
            std::cout << message << std::endl;
            out.close();
        }
        static void debuglog(std::string message)
        {
            #ifdef __DEBUG
            std::ofstream out("logs.log", std::fstream::app);
            out << "[D] " << message << std::endl;
            std::cout << message << std::endl;
            out.close();
            #endif
        }
};

#endif /* !LOGGER_HPP_ */
