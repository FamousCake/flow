#pragma once

#include <iostream>
#include <cstring>
#include <algorithm>

class Graph
{
public:
    Graph(int);
    ~Graph();


    int V;
    int **E;
};

