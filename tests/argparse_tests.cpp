/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** argparse_tests
*/

#include "gtest/gtest.h"
#include "ArgParse.hpp"

TEST(argparse, normal_args)
{
    ASSERT_EQ(ArgParse::isArgsNumberCorrect(4), false); // Checks if 4 arguments is valid
}