// Copyright 2015 Peter
#include <iostream>

#include "inc/globals.h"
#include "inc/io.h"
#include "inc/graph_generation.h"

int main()
{
    int N = 5;

    int E[Globals::MaxGraphSize][Globals::MaxGraphSize];

    //IO::ReadGraph(E, "tests/test1/input");
    GraphGeneration::GenerateRandomGraph(E, N, N-1, 70, 0, 100);

    IO::printArrayDouble(E, "Here you go", 3, N);

    return 0;
}
