// Copyright 2015 Peter
#include <iostream>

#include "inc/globals.h"
#include "inc/io.h"
#include "inc/graph_generation.h"
#include "inc/ford-fulkerson.h"

int main()
{
    int N = 5;

    int E[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            E[i][j] = 0;
        }
    }

    IO::ReadGraph(E, "tests/test1/input");
    //GraphGeneration::GenerateRandomGraph(E, N, 70, 0, 100);

    IO::printArrayDouble(E, "Here you go", 3, N);

    FordFulkerson FF(E, N, 0, N - 1);

    FF.Run();

    IO::printArrayDouble(FF.E, "Here you go", 3, N);

    std::cout << "Flow is : " << FF.GetFlow();

    return 0;
}
