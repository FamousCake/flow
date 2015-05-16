#ifndef RELABEL_TO_FRONT_H
#define RELABEL_TO_FRONT_H

#include <limits>
#include <algorithm>
#include <vector>

#include "globals.h"
#include "vertex.h"
#include "residual_network.h"

class RelabelToFront
{
  public:
    Vertex *V;

    // Residual network
    ResidualNetwork E;

    // Total number of vertices
    int VertexCount;

    // Source and sink index in the network
    int Source, Sink;

    RelabelToFront(const ResidualNetwork &);
    ~RelabelToFront();

    void Run();
    void PushInitialFlow();
    void Discharge(int);

    void Push(int, int);
    void Relabel(int);

    bool IsOverflowing(int);
    bool CanPush(int, int);
    bool CanRelabel(int);
};

#endif // RELABEL_TO_FRONT_H
