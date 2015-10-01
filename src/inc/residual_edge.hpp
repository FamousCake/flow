#ifndef RESIDUAL_EDGE
#define RESIDUAL_EDGE

class ResidualEdge
{
  public:
    ResidualEdge()
    {
        this->from = -1;
        this->to = -1;
        this->weight = -1;
        this->index = -1;
        this->capacity = -1;
    }
    ResidualEdge(int a, int b, int c, int d, int e)
    {
        this->from = a;
        this->to = b;
        this->weight = c;
        this->index = d;
        this->capacity = e;
    }

    ResidualEdge(const ResidualEdge &A)
    {
        this->from = A.from;
        this->to = A.to;
        this->weight = A.weight;
        this->index = A.index;
        this->capacity = A.capacity;
    }

    int from = -1;
    int to = -1;
    int weight = -1;
    int index = -1;
    int capacity = -1;
};

#endif
