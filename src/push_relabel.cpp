#include "inc/push_relabel.h"

void PushRelabel::run(Graph &g, const Graph &o, unsigned const int s,
                      unsigned const t)
{
    PushRelabel::init(g, s);

    while (true) {

        if (PushRelabel::Push(g, o, s, t)) {
            // std::cout << std::endl;
            // io::printGraph(g,3);
            // std::cout << std::endl;
            continue;
        }

        if (PushRelabel::Relabel(g, o, s, t)) {
            // std::cout << std::endl;
            // io::printGraph(g,3);
            // std::cout << std::endl;
            continue;
        }

        break;
    }
}

bool PushRelabel::Push(Graph &g, const Graph &o, unsigned const s,
                       unsigned const t)
{
    for (int i = 0; i < g.VertexCount; ++i) {

        // If the current vertex is overflowing
        // s and t cannot overflow by definition!
        if (i != s && i != t && g.e[i] > 0) {

            for (int j = 0; j < g.VertexCount; ++j) {

                if (g.E[i][j] > 0 && g.h[i] == g.h[j] + 1) {

                    // std::cout << "Push : " << i << " / " << j << std::endl;

                    int min = g.e[i] < g.E[i][j] ? g.e[i] : g.E[i][j];

                    // Important it's o here
                    if (o.E[i][j] > 0) {
                        g.E[i][j] -= min;
                        g.E[j][i] += min;
                    } else {
                        g.E[i][j] += min;
                        g.E[j][i] -= min;
                    }

                    g.e[i] -= min;
                    g.e[j] += min;

                    return true;
                }
            }
        }
    }
    return false;
}

bool PushRelabel::Relabel(Graph &g, const Graph &o, unsigned const s,
                          unsigned const t)
{
    for (int i = 0; i < g.VertexCount; ++i) {

        // If vertex is overflowing.
        // s and t do not overflow by definition!
        if (i != s && i != t && g.e[i] > 0) {

            unsigned int min = std::numeric_limits<int>::max();

            // For each neighbouring vertex, look for the one that is of least height
            for (int j = 0; j < g.VertexCount; ++j) {
                if (g.E[i][j] > 0 && g.h[i] <= g.h[j]) {
                    if (g.h[j] < min) {
                        min = g.h[j];
                    }
                }
            }

            //std::cout << "Relabel : " << i << std::endl;
            // Increase the height of the lowest heighbour plus one
            g.h[i] = 1 + min;

            return true;
        }
    }
    return false;
}

void PushRelabel::init(Graph &g, int source)
{
    for (int i = 0; i < g.VertexCount; ++i) {
        g.e[i] = 0;
        g.h[i] = 0;
        g.V[i] = 0;
    }

    g.h[source] = g.VertexCount;

    for (int i = 0; i < g.VertexCount; ++i) {
        if (g.E[source][i] > 0) {

            g.E[i][source] = g.E[source][i];
            g.E[source][i] = 0;

            g.e[i] += g.E[i][source];
            g.e[source] -= g.E[i][source];
        }
    }
}