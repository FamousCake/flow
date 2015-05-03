#ifndef VERTEX_H
#define VERTEX_H

#include "globals.h"

// Vertex data structure used by RTF
struct Vertex {
    int Index = 0;
    int Height = 0;
    int ExcessFlow = 0;

    // @TODO Think about making this a vector. Would be fast because you only iterate it.
    // int Current = 0;
    // int NCount = 0;
    // int NList[MAX_GRAPH_SIZE];
};

#endif // VERTEX_H
