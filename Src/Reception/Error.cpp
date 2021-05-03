/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(const char *what, const char *where) : _What(what), _Where(where)
{
}

Error::~Error()
{
}

const char *Error::getWhat()
{
    return _What.c_str();
}

const char *Error::getWhere()
{
    return _Where.c_str();
}
