// Copyright 2015 Peter
#include <iostream>
#include <queue>

#include "../inc/graph.h"
#include "../inc/stopwatch.h"
#include "../inc/io.h"
#include "../inc/ford_fulkerson.h"


int main(int argc, char **argv ) {

    std::cout << "\n\n";
    CStopWatch a;
    a.Start();
    
    std::queue<int> q;

    q.push(11);


    Graph g = io::readGraph("tests/test1/input");

    io::printGraph(g, 3);

    io::printGraph(FordFulkerson::Run(g, 0, 4), 3);


    a.Stop();
    std::cout << "\n\nTime is : " << a.GetDuration() << std::endl;

    return 0;
}
