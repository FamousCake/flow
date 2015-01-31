#include "../inc/graph.h"


Graph::Graph(int n)
{
    this->V = n;

    this->E = new int*[n];

    for (int i = 0; i < n; ++i)
    {
        this->E[i] = new int[n];

        // Fastest way to initialize
        memset(this->E[i], 0, sizeof(this->E[i]));

        // Fill is slower
        //std::fill(this->E[i], this->E[i] + n, 11);
    }

}

Graph::~Graph()
{
    delete this->E;
}