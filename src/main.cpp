// Copyright 2015 Peter
#include <iostream>
#include <algorithm>
#include <vector>

#include "inc/io.h"
#include "inc/graph_generation.h"
#include "inc/ford-fulkerson.h"
#include "inc/relabel_to_front.h"
#include "stopwatch/stopwatch.h"

using namespace std;

int GetFlow(const vector<vector<int>> &A, ResidualNetwork &B)
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
    // Initialization
    int N = 100;

    Stopwatch S;
    S.set_mode(REAL_TIME);

    // vector<vector<int>> raw = IO::ReadGraph("tests/test1/input");
    vector<vector<int>> raw = GraphGeneration::GenerateRandomGraph(N, 75, 1, 100000);

    //
    // FORD FULKERSON
    //
    S.start("FF");
    FordFulkerson FF(raw, 0, N - 1);
    FF.Run();
    S.stop("FF");

    //
    // RELABEL TO FRONT
    //
    S.start("RTF");
    RelabelToFront RTF(raw, 0, N-1);
    RTF.Run();
    S.stop("RTF");

    // RESULTS
    cout << endl
         << "FF Flow is : " << GetFlow(raw, FF.E);
    cout << endl << "RTF Flow is : " << GetFlow(raw, RTF.E);

    S.report("FF");
    S.report("RTF");

    std::cout << '\n';
    return 0;
}
