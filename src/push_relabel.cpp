#include "inc/push_relabel.h"

void PushRelabel::run(Graph &g, const Graph &o, unsigned const int s,
                      unsigned const t)
{
    PushRelabel::init(g, s);

    while (true) {

        if (PushRelabel::Push(g, o, s, t)) {
            continue;
        }

        if (PushRelabel::Relabel(g, o, s, t)) {
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

                    int min = g.e[i] < g.E[i][j] ? g.e[i] : g.E[i][j];

                    g.E[i][j] -= min;
                    g.E[j][i] += min;

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

            int flow = g.E[source][i];

            g.E[i][source] += flow;
            g.E[source][i] -= flow;

            g.e[i] += flow;
            g.e[source] -= flow;
        }
    }
}