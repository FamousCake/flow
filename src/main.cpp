// Copyright 2015 Peter
#include <iostream>

#include "inc/globals.h"
#include "inc/io.h"
#include "inc/graph_generation.h"
#include "inc/ford-fulkerson.h"

int main()
{
    int N = 50;
    int E[Globals::MaxGraphSize][Globals::MaxGraphSize];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            E[i][j] = 0;
        }
    }

    // IO::ReadGraph(E, "tests/test1/input");
    GraphGeneration::GenerateRandomGraph(E, N, 70, 0, 100);

    // IO::printArrayDouble(E, "Here you go", 3, N);

    FordFulkerson FF(E, N, 0, N - 1);

    FF.Run();

    // IO::printArrayDouble(FF.E, "Here you go", 3, N);

    return 0;
}
