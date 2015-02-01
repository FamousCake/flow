// Copyright 2015 Peter
#include <iostream>

#include "../inc/graph.h"
#include "../inc/stopwatch.h"
#include "../inc/io.h"
#include "../inc/ford-fulkerson.h"

int main() {

    std::cout << "\n\n";
    CStopWatch a;
    a.Start();







    Graph g = io::readGraph("tests/test1/input");

    io::printGraphEdges(g, 3);


    FordFulkerson::Run(g);
    //FordFulkerson::GetPath(g, 0);



    a.Stop();
    std::cout << "\n\nTime is : " << a.GetDuration() << std::endl;

    return 0;
}
