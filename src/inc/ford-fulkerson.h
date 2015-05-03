// Copyright 2015 Peter

#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H
#include <queue>
#include <iostream>
#include <vector>

#include "simple_queue.h"
#include "globals.h"
#include "residual_network.h"
#include "io.h"

class FordFulkerson
{

  public:
    // List of ancestors for every vertex after the BFS
    int V[MAX_GRAPH_SIZE];

    // Residual network
    ResidualNetwork E;

    // Total number of vertices
    int VertexCount;

    // Source and sink index in the network
    int Source, Sink;

    /**
     * @brief Constructor
     *
     * @param t Original Flow network
     * @param t Number ot vertices
     * @param t Source index
     * @param t Sink index
     */

    FordFulkerson(std::vector<std::vector<int>>, const int, const int);

    void Run();

    int GetFlow();

  private:
    /**
     * @brief Use BFS to find a path sink -> source
     * @details The path is saved in the lsit of ancestors (this->V)
     *
     * @return True if a path exists, false if it does not
     */
    bool GetPath();

    /**
     * @brief Augment flow along a path sink -> source
     * @details Use the list of ancestors to go along the path and augment it with the minimum flow
     */
    void AugmentPath();

    /**
     * @brief Resets the list of ancestors (V)
     * @details [long description]
     */
    void resetVertices();
};

#endif // FORD_FULKERSON_H
