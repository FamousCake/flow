#ifndef RESIDUAL_NETWORK_MATRIX
#define RESIDUAL_NETWORK_MATRIX

#include <vector>
#include <functional>

#include "residual_network.h"
#include "residual_edge.h"

class ResidualNetworkMatrix
{
  public:
    ResidualNetworkMatrix(int, int, int, int);
    ResidualNetworkMatrix(const std::vector<std::vector<ResidualEdge>> &, int, int);
    ResidualNetworkMatrix(const ResidualNetworkMatrix &);

    ~ResidualNetworkMatrix();

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
