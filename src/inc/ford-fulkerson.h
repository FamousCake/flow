// Copyright 2015 Peter

#pragma once

#include "graph.h"
#include "io.h"
#include <queue>
#include <vector>
#include <iostream>

class FordFulkerson {

    public:

        FordFulkerson();
        ~FordFulkerson();

        static Graph Run(Graph);

        static bool GetPath(Graph&, const int, const int);

        static void AugmentPath(Graph&, const int, const int);

};
