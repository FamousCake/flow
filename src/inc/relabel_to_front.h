#ifndef RELABEL_TO_FRONT_H
#define RELABEL_TO_FRONT_H

#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <forward_list>

#include "vertex.hpp"
#include "residual_edge.hpp"
#include "residual_network.h"

class RelabelToFront
{
  public:
    std::vector<Vertex> V;
    std::vector<int> HeightCount;
    std::queue<int> ActiveQueue;

    int VertexCount;
    int Source, Sink;

    int PushCount, RelabelCount, DischargeCount;

    ResidualNetwork E;

    RelabelToFront(const ResidualNetwork &);
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
