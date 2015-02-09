// Copyright 2015 Peter

#include "inc/graph.h"
#include "inc/stopwatch.h"
#include "inc/io.h"
#include "inc/ford_fulkerson.h"
#include "inc/push_relabel.h"

int main()
{
    std::cout << "\n\n";
    CStopWatch a;
    a.Start();

    Graph g = io::readGraph("tests/test1/input");

    io::printGraph(g, 3);

    Graph o(g);

    // io::printGraph(FordFulkerson::Run(g, 0, 4), 3);

    PushRelabel::run(g, o, 0, 4);

    io::printGraph(g, 3);
    io::printGraph(o, 3);

    a.Stop();
    std::cout << "\n\nTime is : " << a.GetDuration() << std::endl;

    return 0;
}
