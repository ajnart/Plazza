/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** main
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Reception/Error.hpp"
#include "Reception/Help.hpp"
#include "Reception/Reception.hpp"

int main(int ac, char **av)
{
    Reception::Reception response;

    try {
        response.setValue(ac, av);
    } catch (Error::Error &e) {
        std::cout << e.getWhat() << "in" << e.getWhere() << '\n';
        return EXIT_FAILURE;
    } catch (Help::Help &h) {
        std::cout << h.getWhat() << '\n';
        return EXIT_SUCCESS;
    }
}
