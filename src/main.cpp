// Copyright 2015 Peter
#include <iostream>
#include <algorithm>
#include <vector>

#include "inc/globals.h"
#include "inc/io.h"
#include "inc/graph_generation.h"
#include "inc/ford-fulkerson.h"
#include "inc/relabel_to_front.h"
#include "inc/vertex.h"
#include "inc/residual_network.h"

using namespace std;

int GetFlow(const vector<vector<int>> &A,ResidualNetwork &B)
{
    int s = 0;
    for (unsigned long i = 0; i < A.size(); ++i) {

        if (A[0][i] > 0 && B.getWeight(i, 0) > 0) {
            s += B.getWeight(i, 0);
        }
    }

    return s;
}

int main()
{
    int N = 5;

    vector<vector<int>> raw = IO::ReadGraph("tests/test1/input");

    // vector<vector<int>> raw = GraphGeneration::GenerateRandomGraph(N, 45, 1, 10);

    FordFulkerson FF(raw, 0, N - 1);
    //
    FF.Run();
    //
    IO::printResidualNetwork(FF.E, "Here you go FF : ", 3);
    // std::cout << std::endl << "Flow is : " << GetFlow(raw, FF.E);
    //
    // // std::cout << "Flow is : " << FF.GetFlow();
    //
    //
    // RelabelToFront RTF(E, N, 0, N-1);
    //
    // RTF.Run();
    //
    // //IO::printArrayDouble(RTF.E, "Here you go RTF : ", 3, N);
    // std::cout << std::endl << "Flow is : " << GetFlow(E, RTF.E, N);
    //
    std::cout << '\n';
    return 0;
}
