#ifndef RELABEL_TO_FRONT_H
#define RELABEL_TO_FRONT_H

#include <limits>
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

#include "globals.h"
#include "vertex.h"
#include "residual_network_matrix.h"
#include "simple_queue.h"

class RelabelToFront
{
  public:
    Vertex *V;
    int *HeightCount;
    std::queue<int> Q;
    int VertexCount;
    int Source, Sink;

    int PushCount, RelabelCount, DischargeCount;

    ResidualNetworkMatrix E;

    RelabelToFront(const ResidualNetworkMatrix &);
    ~RelabelToFront();

    void Run();

  private:
    void PushInitialFlow();
    void Discharge(int);

    void Push(int, int);
    void Relabel(int);
    void Gap(int);

    bool IsOverflowing(int);
    bool CanPush(int, int);
    bool CanRelabel(int);
    void GetPath();
};

#endif // RELABEL_TO_FRONT_H
