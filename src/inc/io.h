#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <exception>


namespace io {

    void printGraphEdges(const Graph &g, int w)
    {
        for (int i = 0; i < g.VertexCount; ++i)
        {
            std::cout << std::endl;
            for (int j = 0; j < g.VertexCount; ++j)
            {
                std::cout << std::setw(w) << g.E[i][j];
            }
        }

    }

    Graph readGraph(char *filename)
    {
        std::ifstream myfile (filename);

        if ( ! myfile.is_open())
        {
            Graph g;
            std::cout << g.VertexCount;
            return g;
        }

        int n;
        myfile >> n;

        Graph g(n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int w;
                myfile >> w;
                g.E[i][j] = w;
            }
        }

        return g;

        myfile.close();
    }
}