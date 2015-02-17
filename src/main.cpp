// Copyright 2015 Peter

#include "inc/graph.h"
#include "inc/stopwatch.h"
#include "inc/io.h"
#include "inc/ford_fulkerson.h"
#include "inc/push_relabel.h"
#include "inc/graph_generation.h"


int getFlow(const Graph &a)
{
    int s = 0;

    for (int i = 0; i < a.VertexCount; ++i)
    {
        s += a.E[a.VertexCount - 1][i];
    }

    return s;
}

int main()
{
    std::cout << "\n\n";
    CStopWatch a;
    a.Start();

    int N = 10;



    Graph g(GraphGeneration::GenerateRandomGraph(N, 40, 1, 100));
    Graph o(g);

    //io::printGraph(g, 3);



    // Graph g = io::readGraph("tests/test1/input");

    // io::printGraph(g, 3);



    io::printGraph(FordFulkerson::Run(g, 0, 9), 3);

    //Graph

    Graph g1(g);

    PushRelabel::run(g1, o, 0, 9);

    io::printGraph(g1, 5);
    // io::printGraph(o, 3);

    std::cout << "Ford-Fulkerson Flow : " << getFlow(FordFulkerson::Run(g,0, N-1)) << std::endl;
    std::cout << "Push Relabel   Flow : " << getFlow(g1) << std::endl;











    a.Stop();
    std::cout << "\n\nTime is : " << a.GetDuration() << std::endl;

    return 0;
}
