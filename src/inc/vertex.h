#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

// Vertex data structure used by RTF
struct Vertex {
    int Index = 0;
    int Height = 0;
    int ExcessFlow = 0;

    std::vector<int> NList;
    std::vector<int>::iterator NCurrent;
};

#endif // VERTEX_H
