#ifndef VERTEX_H
#define VERTEX_H

#include "globals.h"

struct Vertex {
    int Index = 0;
    int Height = 0;
    int ExcessFlow = 0;

    int Current = 0;
    int NCount = 0;
    int NList[MAX_GRAPH_SIZE];
};

#endif // VERTEX_H
