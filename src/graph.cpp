// Copyright 2015 Peter

#include "inc/graph.h"

Graph::Graph(const int n)
{
    this->initialize(n);
}

Graph::Graph(const Graph &g)
{

    this->initialize(g.VertexCount);

    for (int i = 0; i < g.VertexCount; ++i) {
        this->V[i] = g.V[i];
    }

    for (int i = 0; i < g.VertexCount; ++i) {
        for (int j = 0; j < g.VertexCount; ++j) {
            this->E[i][j] = g.E[i][j];
        }
    }
}

void Graph::ApplyToV(std::function<int(int)> c)
{
    for (int i = 0; i < this->VertexCount; ++i) {
        V[i] = c(V[i]);
    }
}

void Graph::initialize(const int n)
{
    this->VertexCount = n;

    this->V = new int[n];
    this->ExcessFlow = new int[n];
    this->Height = new int[n];

    memset(this->V, 0, sizeof(int) * n);
    memset(this->ExcessFlow, 0, sizeof(int) * n);
    memset(this->Height, 0, sizeof(int) * n);

    this->E = new int *[n];
    for (int i = 0; i < n; ++i) {
        this->E[i] = new int[n];
        memset(this->E[i], 0, sizeof(int) * n);
        // Fill is slower
        // std::fill(this->E[i], this->E[i] + n, 11);
    }
}

Graph::~Graph()
{
    delete[] this->E;
    delete[] this->V;
    delete[] this->ExcessFlow;
    delete[] this->Height;
}
