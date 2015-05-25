#ifndef RESIDUAL_NETWORK_LIST
#define RESIDUAL_NETWORK_LIST

#include <vector>

#include "residual_network.h"
#include "residual_edge.h"

class ResidualNetworkList
{
  public:
    ResidualNetworkList(const std::vector<std::vector<ResidualEdge>> &, int, int);
    ResidualNetworkList(const ResidualNetworkList &);

    int getWeight(int, int);
    void setWeight(int, int, int);
    void updateWeight(int, int, int);

    int getCount();
    int getEdgesCount();
    int getSource();
    int getSink();
    int getFlow();

    ResidualEdge &getEdge(int, int);
    std::vector<ResidualEdge> &getNeighbours(int);

    std::vector<std::vector<ResidualEdge>> E;

  private:
    int Count;
    int Source, Sink;
};

#endif
