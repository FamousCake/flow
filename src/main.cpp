// Copyright 2015 Peter
#include <iostream>
#include <vector>

#include "inc/io.h"
#include "inc/graph_generation.h"
#include "inc/ford-fulkerson.h"
#include "inc/relabel_to_front.h"
#include "stopwatch/stopwatch.h"
#include "inc/residual_network.h"
#include "stanford.cpp"

using namespace std;

int GetFlow(ResidualNetwork &B)
{
    int s = 0;
    for (int i = 0; i < B.getCount(); ++i)
    {
        s += B.getWeight(B.getSink(), i);
    }

    return s;
}

long long GetStanfordFlow(ResidualNetwork &E)
{
    PushRelabel PR(E.getCount());

    for (int i = 0; i < E.getCount(); ++i)
    {
        for (int j = 0; j < E.getCount(); ++j)
        {
            if (E.getWeight(i, j) > 0)
            {
                PR.AddEdge(i, j, E.getWeight(i, j));
            }
        }
    }

    return PR.GetMaxFlow(E.getSource(), E.getSink());
}

int main()
{
    Stopwatch S;
    S.set_mode(REAL_TIME);

    //
    // Initialization
    //
    //

    // int N = 10000;
    // cin >> N;
    // vector<vector<int>> raw = GraphGeneration::GenerateRandomGraph(N, 80, 1, 1000);
    // ResidualNetwork E(raw, 0, N - 1);

    // ResidualNetworkMatrix E = IO::ReadGraph();
    ResidualNetworkMatrix E = IO::ReadGraph();
    int edgeCount = E.getEdgesCount();

    //
    // RELABEL TO FRONT
    //
    S.start("RTF");
    RelabelToFront RTF(E);
    RTF.Run();
    S.stop("RTF");

    //
    // FORD FULKERSON
    //
    S.start("FF");
    // FordFulkerson FF(E);
    // FF.Run();
    S.stop("FF");

    //
    // Stanford
    //
    S.start("S");
    // long long flowS = GetStanfordFlow(E);
    S.stop("S");

    //
    // RESULTS
    //
    // cout << "c FF Flow is  : " << GetFlow(FF.E);
    cout << "\n";
    cout << "\n";
    cout << "\n V = " << E.getCount();
    cout << "\n E = " << edgeCount;
    cout << "\n RTF Flow is : " << RTF.E.getFlow();
    // cout << "\n Sta Flow is : " << flowS;

    cout << "\n";
    // cout << "\nc FF Time is  : " << S.get_total_time("FF");
    cout << "\n RTF Time is : " << S.get_total_time("RTF");
    // cout << "\n Sta Time is : " << S.get_total_time("S");

    // cout << "\nc";
    // cout << "\nc";
    // cout << "\nc Iterations Count: " << FF.IterationsCount;
    // cout << "\nc Relabel Count : " << RTF.RelabelCount;
    // cout << "\nc Push Count : " << RTF.PushCount;
    // cout << "\nc Discharge Count : " << RTF.DischargeCount;

    // for (int i = 0; i < E.getCount(); ++i) {
    //     if (FF.testV[i] == -1) {
    //         cout << "\nc " << i << " has not been used...";
    //     }
    // }
    //
    // int count = 0;
    // int count2 = 0;
    //
    // for (int i = 0; i < E.getCount(); ++i) {
    //     if (E.getWeight(E.getSource(), i) > 0) {
    //         count++;
    //     }
    //     if (E.getWeight(i, E.getSink()) > 0) {
    //         count2++;
    //     }
    // }
    //
    // cout <<"\nc Edges sticking from the source : " << count;
    // cout <<"\nc Edges sticking from the sink : " << count2;

    // for (int i = 0; i < E.getCount(); ++i) {
    //     cout << "c " << i << " : " << RTF.V[i].RelabelCount << " time RELABELED"<< endl;
    // }
    //
    // for (int i = 0; i < E.getCount(); ++i) {
    //     cout << "c " << i << " : " << RTF.V[i].PushCount << " time PUSHED"<< endl;
    // }
    // IO::WriteGraph(E);

    // for (auto i : raw) {
    //     cout << endl;
    //     for(auto j: i) {
    //         cout << j << " ";
    //     }
    // }

    // IO::printResidualNetwork(E, 3, "E");
    // IO::printResidualNetwork(FF.E, "FF", 3);
    // IO::printResidualNetwork(RTF.E, "RTF", 3);

    cout << endl;
    return 0;
}
