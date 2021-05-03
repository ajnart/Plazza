/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Help
*/

#ifndef HELP_HPP_
#define HELP_HPP_

#include <iostream>

class Help {
    private:
        std::string _What;
    public:
        Help();
        ~Help();
        const char *getWhat();
};

#endif /* !HELP_HPP_ */
