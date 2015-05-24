#ifndef RESIDUAL_NETWORK
#define RESIDUAL_NETWORK

#include <vector>
#include <functional>

class ResidualNetwork
{
  public:
    /**
     * Construct empty residual network
     *
     * @param count Vertex Count
     * @param value Initial value ot all edges
     */
    ResidualNetwork(int, int, int, int);

    /**
     * Construct a residual network from 2D Vector
     *
     * @param v Raw edge data
     */
    ResidualNetwork(const std::vector<std::vector<int>> &, int, int);

    ResidualNetwork(const ResidualNetwork &);

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
    int getEdgesCount();
    int getSource();
    int getSink();

    int **getRaw();

    // I don't use this, but just in case
    void eachEdge(std::function<void(int, int, int)>);

  private:
    int Count;
    int **E;
    int Source, Sink;
};

#endif
