// Copyright 2015 Peter
#include <iostream>

#include "inc/globals.h"
#include "inc/io.h"
#include "inc/graph_generation.h"
#include "inc/ford-fulkerson.h"
#include "inc/relabel_to_front.h"
#include "inc/vertex.h"

int GetFlow(int A[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE],int B[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE], int N)
{
    int s = 0;
    for (int i = 0; i < N; ++i)
    {
        if (A[0][i] > 0 && B[i][0] > 0) {
            s += B[i][0];
        }
    }

    return s;

}

int main()
{
    //Vertex A[MAX_GRAPH_SIZE];

    int N = 300;

    int E[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            E[i][j] = 0;
        }
    }

    //IO::ReadGraph(E, "tests/test1/input");
    GraphGeneration::GenerateRandomGraph(E, N, 100, 0, 1000);

    //IO::printArrayDouble(E, "Here you go", 3, N);

    FordFulkerson FF(E, N, 0, N - 1);

    FF.Run();

    //IO::printArrayDouble(FF.E, "Here you go FF : ", 3, N);
    std::cout << std::endl << "Flow is : " << GetFlow(E, FF.E, N);

    // std::cout << "Flow is : " << FF.GetFlow();


    RelabelToFront RTF(E, N, 0, N-1);

    RTF.Run();

    //IO::printArrayDouble(RTF.E, "Here you go RTF : ", 3, N);
    std::cout << std::endl << "Flow is : " << GetFlow(E, RTF.E, N);

    return 0;
}
