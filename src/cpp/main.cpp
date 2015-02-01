// Copyright 2015 Peter
#include <iostream>

#include "../inc/graph.h"
#include "../inc/stopwatch.h"
#include "../inc/io.h"
#include "../inc/ford-fulkerson.h"
#include "../inc/linked_list.h"

int main() {

    std::cout << "\n\n";
    CStopWatch a;
    a.Start();



    //LinkedList l;

    //l.Add(11,5);

    LinkedList p;
    p.Add(11,4);
    p.Add(11,4);
    p.Add(11,4);
    p.Add(11,4);


    ListNode *x = p.start;

    while(x)
    {
        std::cout << x->v <<" ";
        x = x->next;
    }



    Graph g = io::readGraph("tests/test1/input");

    io::printGraph(g, 3);

    io::printGraph(FordFulkerson::Run(g), 3);




    a.Stop();
    std::cout << "\n\nTime is : " << a.GetDuration() << std::endl;

    return 0;
}
