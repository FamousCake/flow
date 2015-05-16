#ifndef RELABEL_TO_FRONT_H
#define RELABEL_TO_FRONT_H

#include <limits>
#include <iostream>
#include <algorithm>

#include "globals.h"
#include "vertex.h"
#include "residual_network.h"

class RelabelToFront
{
  public:
    Vertex *V;
    int VertexCount;
    int Source, Sink;

    int PushCount, RelabelCount, DischargeCount;

    ResidualNetwork E;

    RelabelToFront(const ResidualNetwork &);
    ~RelabelToFront();

    void Run();

  private:
    void PushInitialFlow();
    void Discharge(int);

    void Push(int, int);
    void Relabel(int);

    bool IsOverflowing(int);
    bool CanPush(int, int);
    bool CanRelabel(int);
};

#endif // RELABEL_TO_FRONT_H
