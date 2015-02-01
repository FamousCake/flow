// Copyright 2015 Peter

#pragma once

#include <iostream>
#include <cstring>
// #include <algorithm>

class Graph {
 public:
    // Default Const for an Empty Graph
    Graph() : VertexCount(0), V(NULL), E(NULL) {}

    explicit Graph(int n);

    ~Graph();

    int VertexCount = 0;
    int *V = NULL;
    int **E = NULL;
};

