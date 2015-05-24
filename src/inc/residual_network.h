#ifndef RESIDUAL_NETWORK
#define RESIDUAL_NETWORK

#include <vector>

class ResidualNetwork
{
  public:

    virtual int getWeight(int, int) = 0;
    virtual void setWeight(int, int, int) = 0;
    virtual void updateWeight(int, int, int) = 0;

    virtual int getCount() = 0;
    virtual int getEdgesCount() = 0;
    virtual int getSource() = 0;
    virtual int getSink() = 0;

    virtual std::vector<std::vector<int>> getRaw() = 0;
};

#endif
