// Copyright 2015 Peter

#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H
#include <queue>
#include <iostream>

#include "simple_queue.h"
#include "globals.h"

class FordFulkerson
{

  public:
    // List of ancestors for every vertex after the BFS
    int V[Globals::MaxGraphSize];

    // Residual network
    int E[Globals::MaxGraphSize][Globals::MaxGraphSize];

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

    FordFulkerson(int[][Globals::MaxGraphSize], const int, const int, const int);

    void Run();

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
