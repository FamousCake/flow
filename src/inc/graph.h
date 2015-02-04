// Copyright 2015 Peter

#pragma once

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

    void ApplyToV(std::function<int(int)>);

  private:
    void initialize(const int);
};
