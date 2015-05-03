#ifndef RESIDUAL_NETWORK
#define RESIDUAL_NETWORK

#include <algorithm>
#include <vector>
#include <iostream>

class ResidualNetwork
{
  public:
    ResidualNetwork(int, int);
    ResidualNetwork(const std::vector<std::vector<int>> &);
    ~ResidualNetwork();

    int getWeight(int, int);
    void setWeight(int, int, int);

    int getCount();

    int **getRaw();

  private:
    int Count;
    int **E;
};

#endif
