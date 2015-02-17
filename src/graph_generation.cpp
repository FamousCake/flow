
#include "inc/graph_generation.h"

Graph GraphGeneration::GenerateRandomGraph(int vertexCount, int density, int min, int max)
{
    Graph a(vertexCount);

    std::random_device rd;

    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(min, max);
    std::uniform_int_distribution<int> dist2(1, 100);

    for (int i = 0; i < a.VertexCount - 1; ++i) {
        for (int j = 0; j < a.VertexCount; ++j) {
            if (i != j && dist2(mt) <= density && a.E[j][i] == 0) {
                a.E[i][j] = dist(mt);
            }
        }
    }

    return a;
}