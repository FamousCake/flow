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

auto GetStanfordFlow(ResidualNetworkList &E) -> PushRelabel
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

    return PR;//.GetMaxFlow(E.getSource(), E.getSink());
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
    ResidualNetworkList E = IO::ReadGraphList();
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
    // S.start("FF");
    // FordFulkerson FF(E);
    // FF.Run();
    // S.stop("FF");

    //
    // Stanford
    //
    // S.start("S");
    // auto PR = GetStanfordFlow(E);
    // long long flowS = PR.GetMaxFlow(E.getSource(), E.getSink());//GetStanfordFlow(E);
    // S.stop("S");

    //
    // RESULTS
    //
    // cout << "c FF Flow is  : " << GetFlow(FF.E);
    cout << "V : " << E.getCount() << endl;
    cout << "E : " << edgeCount << endl;
    // cout << "FF Flow is : " << FF.E.getFlow() << endl;
    cout << "RTF Flow is : " << RTF.E.getFlow() << endl;
    // cout << "\n Sta Flow is : " << flowS << endl;

    // cout << "FF Time is : " << S.get_total_time("FF") << endl;
    cout << "RTF Time is : " << S.get_total_time("RTF") << endl;
    // cout << "Sta Time is : " << S.get_total_time("S") << endl;

    // cout << "\nc";
    // cout << "\nc";
    // cout << "Iterations : " << FF.IterationsCount << endl;
    cout << "Relabel Count : " << RTF.RelabelCount << endl;
    cout << "Push Count : " << RTF.PushCount << endl;
    cout << "Discharge Count : " << RTF.DischargeCount << endl;

    cout << "\n";
    cout << "\n";

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
