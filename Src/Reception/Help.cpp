/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Help
*/

#include "Help.hpp"

Help::Help() : _What("USAGE: 3 arguments\n")
{
}

Help::~Help()
{
}

const char *Help::getWhat()
{
    return _What.c_str();
}