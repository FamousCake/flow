#ifndef RELABEL_TO_FRONT_H
#define RELABEL_TO_FRONT_H

#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

#include "vertex.hpp"
#include "simple_queue.hpp"
#include "residual_edge.h"
#include "residual_network_list.h"

class RelabelToFront
{
  public:
    std::vector<Vertex> V;
    std::vector<int> HeightCount;
    std::queue<int> ActiveQueue;

    int VertexCount;
    int Source, Sink;

    int PushCount, RelabelCount, DischargeCount;

    ResidualNetworkList E;

    RelabelToFront(const ResidualNetworkList &);
    ~RelabelToFront();

    void Run();

  private:
    void SetInitialLabels();

    void Discharge(const int);

    void Push(ResidualEdge &);
    void Relabel(const int);
    void Gap(const int);

    bool CanPush(const ResidualEdge &);
    bool CanRelabel(const int);
    bool IsOverflowing(const int);
};

#endif // RELABEL_TO_FRONT_H
