// Copyright 2015 Peter
#include <iostream>
#include <algorithm>
#include <vector>

#include "inc/io.h"
#include "inc/graph_generation.h"
#include "inc/ford-fulkerson.h"
#include "inc/relabel_to_front.h"
#include "stopwatch/stopwatch.h"
#include "inc/residual_network.h"

using namespace std;

int GetFlow(ResidualNetwork &B, int sink)
{
    int s = 0;
    for (int i = 0; i < B.getCount(); ++i) {
        s += B.getWeight(sink, i);
    }

    return s;
}

int main()
{
    cout << " Enter you graph : " << endl;
    // Initialization
    int N = 6;

    Stopwatch S;
    S.set_mode(REAL_TIME);

    ResidualNetwork E = IO::ReadGraph();
    // vector<vector<int>> raw = GraphGeneration::GenerateRandomGraph(N, 75, 1, 100000);

    //
    // FORD FULKERSON
    //
    S.start("FF");
    FordFulkerson FF(E, 0, N - 1);
    FF.Run();
    S.stop("FF");

    //
    // RELABEL TO FRONT
    //
    S.start("RTF");
    RelabelToFront RTF(E, 0, N-1);
    RTF.Run();
    S.stop("RTF");

    // RESULTS
    cout << endl
         << "FF Flow is  : " << GetFlow(FF.E, N - 1);

    cout << endl
         << "RTF Flow is : " << GetFlow(RTF.E, N - 1);

    S.report("FF");
    S.report("RTF");

    // for (auto i : raw) {
    //     cout << endl;
    //     for(auto j: i) {
    //         cout << j << " ";
    //     }
    // }

    IO::printResidualNetwork(E, "E", 3);
    IO::printResidualNetwork(FF.E, "FF", 3);
    IO::printResidualNetwork(RTF.E, "RTF", 3);

    std::cout << '\n';
    return 0;
}
