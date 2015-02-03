// Copyright 2015 Peter

#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include "graph.h"
#include "simple_queue.h"

namespace FordFulkerson {

    /**
     * @brief Runs the Ford-Fulkerson Algorithim
     *
     * @param h Input Graph
     * @param t Source Index
     * @param t Sink Index
     * @return Ending Residual Network
     */
    Graph Run(Graph, const int, const int);

    /**
     * @brief Find a path from the source to the sink in the residual network.
     *
     * @param g Input graph(must be a residual network)
     * @param source
     * @param sink
     * @return Whether a path has been fouth. Path info is in g.V (list of parrents)
     */
    bool GetPath(Graph& g, const int source, const int sink);

    /**
     * @brief Augment a path in the residual network according to the Min Cut Max Flow theorem
     *
     * @param h Input graph(must be a residual network)
     * @param t source
     * @param t sink
     */
    void AugmentPath(Graph&, const int, const int);
};

#endif // FORD_FULKERSON_H
