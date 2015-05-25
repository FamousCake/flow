#ifndef RESIDUAL_NETWORK_MATRIX
#define RESIDUAL_NETWORK_MATRIX

#include <vector>
#include <functional>

#include "residual_network.h"

class ResidualNetworkMatrix
{
  public:
    /**
     * Construct empty residual network
     *
     * @param count Vertex Count
     * @param value Initial value ot all edges
     */
    ResidualNetworkMatrix(int, int, int, int);

    /**
     * Construct a residual network from 2D Vector
     *
     * @param v Raw edge data
     */
    ResidualNetworkMatrix(const std::vector<std::vector<std::pair<int, int>>> &, int, int);

    ResidualNetworkMatrix(const ResidualNetworkMatrix &);

    /**
     * Copy Constructor
     */
    // @TODO Make this work somehow...
    // ResidualNetwork(ResidualNetwork&);

    ~ResidualNetworkMatrix();

    int getWeight(int, int);
    void setWeight(int, int, int);
    void updateWeight(int, int, int);

    int getCount();
    int getEdgesCount();
    int getSource();
    int getSink();
    int getFlow();

    // std::vector<std::vector<int>> getRaw();
    std::vector<std::vector<std::pair<int, int>>> E;

    // I don't use this, but just in case
    // void eachEdge(std::function<void(int, int, int)>);

  private:
    int Count;
    // int **E;
    int Source, Sink;
};

#endif
