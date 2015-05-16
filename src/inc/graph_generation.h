#ifndef GRAPH_GENERATION_H
#define GRAPH_GENERATION_H

#include <random>
#include <iostream>
#include <vector>

#include "globals.h"

class GraphGeneration
{
  public:
    static inline std::vector<std::vector<int>> GenerateRandomGraph(int count, int density, int min, int max)
    {
        std::vector<std::vector<int>> E(count, std::vector<int>(count, 0));

        std::random_device rd;
        std::mt19937 mt(rd());

        std::uniform_int_distribution<int> dist(min, max);
        std::uniform_int_distribution<int> dist2(1, 100);
        std::uniform_int_distribution<int> dist3(1, 2);

        // No edges can go out of the sink
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (dist2(mt) <= density) {

                    // the Source and Sink are special cases
                    if (i == 0) {
                        E[i][j] = dist(mt);
                    } else if (j == count - 1) {
                        E[i][j] = dist(mt);
                    }

                    else {
                        E[i][j] = dist(mt);
                        // if (dist3(mt) == 1) {
                        //     E[i][j] = dist(mt);
                        // } else {
                        //     E[j][i] = dist(mt);
                        // }
                    }
                }
            }
        }

        return E;
    }
};

#endif // GRAPH_GENERATION_H
