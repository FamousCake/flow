// Copyright 2015 Peter

#pragma once

#include "graph.h"
#include <queue>

class FordFulkerson {

    public:

        FordFulkerson();
        ~FordFulkerson();

        static Graph Run(Graph);

        static int* GetPath(Graph);

};
