// Copyright 2015 Peter

#include <iostream>

#include "../inc/graph.h"
#include "../inc/stopwatch.h"
#include "../inc/io.h"

int main() {
    CStopWatch a;
    a.Start();

    Graph g = io::readGraph("tests/test1/inputz");
    io::printGraphEdges(g, 3);

    Graph z(10);

    a.Stop();

    std::cout << std::endl << "Time is : " << a.GetDuration();


    return 0;
}
