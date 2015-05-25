#ifndef RESIDUAL_NETWORK_LIST
#define RESIDUAL_NETWORK_LIST

#include <vector>

#include "residual_network.h"

class ResidualNetworkList
{
  public:
    ResidualNetworkList(const std::vector<std::vector<std::pair<int, int>>> &, int, int);
    ResidualNetworkList(const ResidualNetworkList &);

    int getWeight(int, int);
    void setWeight(int, int, int);
    void updateWeight(int, int, int);

    int getCount();
    int getEdgesCount();
    int getSource();
    int getSink();
    int getFlow();

    // std::vector<std::pair<int,int>> getNeighbours(int);

    std::vector<std::vector<std::pair<int, int>>> E;

  private:
    int Count;
    int Source, Sink;
};

#endif
