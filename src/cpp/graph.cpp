// Copyright 2015 Peter

#include "../inc/graph.h"


Graph::Graph(int n) {
    this->VertexCount = n;

    this->V = new int[n];
    memset(this->V, 0, sizeof(int) * n );


    this->E = new int*[n];
    for (int i = 0; i < n; ++i) {
        this->E[i] = new int[n];

        // Fastest way to initialize
        memset(this->E[i], 0, sizeof(int) * n);

        // Fill is slower
        // std::fill(this->E[i], this->E[i] + n, 11);
    }
}

Graph::~Graph() {
    delete [] this->E;
    delete [] this->V;
}
