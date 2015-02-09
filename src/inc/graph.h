// Copyright 2015 Peter

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstring>
#include <functional>
#include <memory>

// #include <algorithm>

class Graph
{
  public:
    // Default Const for an Empty Graph
    Graph()
    {
    }
    Graph(const int n);
    Graph(const Graph &);
    ~Graph();

    int VertexCount = 0;

    int *V = NULL;
    int **E = NULL;

    void ApplyToV(const std::function<int(int)>);

  private:
    void initialize(const int);
};

#endif // GRAPH_HP
