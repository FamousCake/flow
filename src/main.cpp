// Copyright 2015 Peter
#include <iostream>
#include <vector>

#include "inc/io.h"
#include "stopwatch/stopwatch.h"

#include "inc/ford-fulkerson.h"
#include "inc/relabel_to_front.h"
#include "inc/residual_network.h"
#include "stanford.cpp"

using namespace std;

auto GetStanfordFlow(ResidualNetwork &E) -> PushRelabel
{
    PushRelabel PR(E.getCount());

    for (int i = 0; i < E.getCount(); ++i)
    {
        for (auto edge : E.getOutgoingEdges(i))
        {
            if (edge.weight > 0)
            {
                PR.AddEdge(edge.from, edge.to, edge.weight);
            }
        }
    }

    return PR;
}

int main()
{
    Stopwatch S;
    S.set_mode(REAL_TIME);

    //
    // Initialization
    //
    ResidualNetwork E = IO::ReadGraph();

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
    FordFulkerson FF(E);
    FF.Run();
    S.stop("FF");

    //
    // Stanford
    //
    S.start("S");
    auto PR = GetStanfordFlow(E);
    long long flowS = PR.GetMaxFlow(E.getSource(), E.getSink());
    S.stop("S");

    //
    // RESULTS
    //
    cout << "Vertices    : " << E.getCount() << endl;
    cout << "Edges       : " << E.getEdgesCount() << endl;
    cout << "\n";
    cout << "RTF Flow is : " << RTF.E.getFlow() << endl;
    cout << "Sta Flow is : " << flowS << endl;
    cout << "FF  Flow is : " << FF.E.getFlow() << endl;
    cout << "\n";
    cout << "RTF Time is : " << S.get_total_time("RTF") << endl;
    cout << "Sta Time is : " << S.get_total_time("S") << endl;
    cout << "FF  Time is : " << S.get_total_time("FF") << endl;
    cout << "\n";
    cout << "FF Paths    : " << FF.IterationsCount << endl;
    cout << "\n";
    cout << "Push        : " << RTF.PushCount << endl;
    cout << "Relabel     : " << RTF.RelabelCount << endl;
    cout << "Discharge   : " << RTF.DischargeCount << endl;

    cout << "\n";
    cout << "\n";

    return 0;
}
