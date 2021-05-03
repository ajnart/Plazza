/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <iostream>

class Error {
    private:
        std::string _What;
        std::string _Where;
    public:
        Error(const char *what, const char *where);
        ~Error();
        const char *getWhat();
        const char *getWhere();
};

#endif /* !ERROR_HPP_ */
