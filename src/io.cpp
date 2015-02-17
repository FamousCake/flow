#include "inc/io.h"

void io::printGraph(const Graph &g, int w)
{
    std::cout << std::endl;
    printGraphV(g, w);
    printGraphExcessFlow(g, w);
    printGraphHeight(g, w);
    printGraphE(g, w);
}

void io::printGraphV(const Graph &g, int w)
{
    std::cout << std::endl;

    std::cout << "V pointer at : " << g.V << std::endl;

    for (int i = 0; i < g.VertexCount; ++i) {
        std::cout << std::setw(w) << g.V[i];
    }
}

void io::printGraphExcessFlow(const Graph &g, int w)
{
    std::cout << std::endl;

    std::cout << "e pointer at : " << g.ExcessFlow << std::endl;

    for (int i = 0; i < g.VertexCount; ++i) {
        std::cout << std::setw(w) << g.ExcessFlow[i];
    }
}

void io::printGraphHeight(const Graph &g, int w)
{
    std::cout << std::endl;

    std::cout << "h pointer at : " << g.Height << std::endl;

    for (int i = 0; i < g.VertexCount; ++i) {
        std::cout << std::setw(w) << g.Height[i];
    }
}

void io::printGraphE(const Graph &g, int w)
{
    std::cout << std::endl;

    std::cout << "E pointer at : " << g.E;

    for (int i = 0; i < g.VertexCount; ++i) {
        std::cout << std::endl;
        for (int j = 0; j < g.VertexCount; ++j) {
            std::cout << std::setw(w) << g.E[i][j];
        }
    }
}

Graph io::readGraph(const char *filename)
{
    std::ifstream myfile(filename);

    if (!myfile.is_open()) {
        Graph g;
        return g;
    }

    int n;
    myfile >> n;

    Graph g(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            myfile >> w;
            g.E[i][j] = w;
        }
    }

    myfile.close();

    return g;
}