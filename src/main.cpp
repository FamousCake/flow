// Copyright 2015 Peter

#include "inc/graph.h"
#include "inc/stopwatch.h"
#include "inc/io.h"
#include "inc/ford_fulkerson.h"
#include "inc/push_relabel.h"
#include "inc/graph_generation.h"
//#include "inc/dual_linked_list.h"

// Sums all the flowing going in the sink
int getFlow(const Graph &a)
{
    int s = 0;

    for (int i = 0; i < a.VertexCount; ++i) {
        s += a.E[a.VertexCount - 1][i];
    }

    return s;
}

int main()
{
    std::cout << "\n\n";
    CStopWatch a, b, c, t;
    a.Start();
    t.Start();

    int N = 5;

    std::cin >> N;

    // Vertex Count, Density, Min , Max (Flow Capasity for all edges)
    Graph g(GraphGeneration::GenerateRandomGraph(N, 70, 1, 1000));
    //Graph g = io::readGraph("tests/test1/input");

    // a.Stop();
    // std::cout << "Generated in : " << a.GetDuration() << std::endl;

    Graph g1(g);

    // FordFulkerson::Run(g, 0, N - 1);

    // b.Start();
    //std::cout << "Ford-Fulkerson Flow : " << getFlow(FordFulkerson::Run(g, 0, N - 1)) << std::endl;

    // b.Stop();
    // std::cout << "Ford-Fulkerson in : " << b.GetDuration() << std::endl;

    // c.Start();
    PushRelabel::run(g1, 0, N - 1);
    std::cout << "Push Relabel   Flow : " << getFlow(g1) << std::endl;

    // c.Stop();
    // std::cout << "Push Relabel in : " << c.GetDuration() << std::endl;

    // t.Stop();
    // std::cout << "\n\nTime is : " << t.GetDuration() << std::endl;

    return 0;
}
