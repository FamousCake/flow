#ifndef RELABEL_TO_FRONT_H
#define RELABEL_TO_FRONT_H

#include <limits>
#include <algorithm>

#include "globals.h"
#include "vertex.h"

class RelabelToFront
{
  public:
    Vertex V[MAX_GRAPH_SIZE];

    // Residual network
    int E[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];

    // Total number of vertices
    int VertexCount;

    // Source and sink index in the network
    int Source, Sink;

    RelabelToFront(int[][MAX_GRAPH_SIZE], const int, const int, const int);
    ~RelabelToFront();

    void Run();

    bool IsOverflowing(int);

    int FindOverflowing();

    void PushInitialFlow();

    void Discharge(int);

    bool CanPush(int, int);
    bool CanRelabel(int);

    void Push(int, int);
    void Relabel(int);
};

#endif // RELABEL_TO_FRONT_H
