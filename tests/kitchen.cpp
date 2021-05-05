/*
** EPITECH PROJECT, 2021
** Plazza [SSH: elitebook]
** File description:
** kitchen
*/

#include "gtest/gtest.h"
#include "Kitchen.hpp"

TEST(Kitchen, status)
{
    Plazza::Kitchen k{5, 2000, 2};
    k.status();
    k.stop();
    ASSERT_EQ(0, 0);
}