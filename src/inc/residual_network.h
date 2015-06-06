#ifndef RESIDUAL_NETWORK
#define RESIDUAL_NETWORK

#include <vector>

#include "residual_network.h"
#include "residual_edge.hpp"

class ResidualNetwork
{
  public:
    ResidualNetwork(const std::vector<std::vector<ResidualEdge>> &, int, int);
    ResidualNetwork(const ResidualNetwork &);

    int getCount();
    int getEdgesCount();

    int getSource();
    int getSink();
    int getFlow();

    ResidualEdge &getEdge(int, int);
    ResidualEdge &getReverseEdge(const ResidualEdge&);
    std::vector<ResidualEdge> &getOutgoingEdges(int);

    std::vector<std::vector<ResidualEdge>> E;

  private:
    int Count;
    int Source, Sink;
};

#endif
