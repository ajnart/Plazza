/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** main
*/

#include <iostream>
#include <string>

#include "ArgParse.hpp"
#include "PlazzaException.hpp"

namespace Plazza {
int plazza(params_t);
}  // namespace Plazza

int main(int ac, char **av) {
    if (!ArgParse::isArgsNumberCorrect(ac)) {
        if (av[1] &&
            (std::string(av[1]) == "-h" || std::string(av[1]) == "--help")) {
            ArgParse::printHelp();
            return 0;
        }
    }
    params_t params;
    try {
        params = ArgParse::ParseArgs(av);
    } catch (Plazza::PlazzaException exp) {
        std::cout << exp.what();
        ArgParse::printHelp();
        return 84;
    }

    return Plazza::plazza(params);
}
