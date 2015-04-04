// Copyright 2015 Peter
#include <iostream>

#include "inc/globals.h"
#include "inc/io.h"

int main()
{
    int N = 5;

    int E[Globals::MaxGraphSize][Globals::MaxGraphSize];

    IO::ReadGraph(E, "tests/test1/input");

    IO::printArrayDouble(E, "Here you go", 3, N);

    return 0;
}
