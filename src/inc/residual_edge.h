#ifndef RESIDUAL_EDGE
#define RESIDUAL_EDGE

class ResidualEdge
{
  public:
    ResidualEdge(int a, int b, int c)
    {
        this->from = a;
        this->to = b;
        this->weight = c;
    }

    ResidualEdge(const ResidualEdge &A)
    {
        this->from = A.from;
        this->to = A.to;
        this->weight = A.weight;
    }

    int from = -1;
    int to = -1;
    int weight = -1;
};

#endif
