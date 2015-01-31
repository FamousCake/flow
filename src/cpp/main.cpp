#include <iostream>
#include "../inc/graph.h"
#include "../inc/stopwatch.h"
#include <functional>
#include <memory>



int main ()
{
    CStopWatch a;

    a.Start();

    Graph g(10000);

    a.Stop();

    std::cout << a.GetDuration();

    return 0;
}
