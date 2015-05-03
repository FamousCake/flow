#ifndef RESIDUAL_NETWORK
#define RESIDUAL_NETWORK

#include <algorithm>
#include <vector>
#include <iostream>

class ResidualNetwork
{
  public:
    /**
     * Construct empty residual network
     *
     * @param count Vertex Count
     * @param value Initial value ot all edges
     */
    ResidualNetwork(int, int);

    /**
     * Construct a residual network from 2D Vector
     *
     * @param v Raw edge data
     */
    ResidualNetwork(const std::vector<std::vector<int>> &);

    /**
     * Copy Constructor
     */
    // @TODO Make this work somehow...
    // ResidualNetwork(ResidualNetwork&);

    ~ResidualNetwork();

    int getWeight(int, int);
    void setWeight(int, int, int);
    void updateWeight(int, int, int);

    int getCount();

    int **getRaw();

  private:
    int Count;
    int **E;
};

#endif
