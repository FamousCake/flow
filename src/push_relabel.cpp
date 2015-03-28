#include "inc/push_relabel.h"

void PushRelabel::run(Graph &residual_network, const int s, const int t)
{
    PushRelabel::init(residual_network, s);

    while (true) {

        if (PushRelabel::Push(residual_network, s, t)) {
            continue;
        }

        if (PushRelabel::Relabel(residual_network, s, t)) {
            continue;
        }

        break;
    }
}

bool PushRelabel::Push(Graph &residual_network, const int s, const int t)
{
    for (int i = 0; i < residual_network.VertexCount; ++i) {

        // If the current vertex is overflowing
        // s and t cannot overflow by definition!
        if (i != s && i != t && residual_network.ExcessFlow[i] > 0) {

            for (int j = 0; j < residual_network.VertexCount; ++j) {

                if (residual_network.E[i][j] > 0 &&
                    residual_network.Height[i] == residual_network.Height[j] + 1) {

                    int min = std::min(residual_network.ExcessFlow[i], residual_network.E[i][j]);

                    residual_network.E[i][j] -= min;
                    residual_network.E[j][i] += min;

                    residual_network.ExcessFlow[i] -= min;
                    residual_network.ExcessFlow[j] += min;

                    return true;
                }
            }
        }
    }
    return false;
}

bool PushRelabel::Relabel(Graph &residual_network, const int s, const int t)
{
    for (int i = 0; i < residual_network.VertexCount; ++i) {

        // If vertex is overflowing.
        // s and t do not overflow by definition!
        if (i != s && i != t && residual_network.ExcessFlow[i] > 0) {

            int min = std::numeric_limits<int>::max();

            // For each neighbouring vertex, look for the one that is of least height
            for (int j = 0; j < residual_network.VertexCount; ++j) {
                if (residual_network.E[i][j] > 0 &&
                    residual_network.Height[i] <= residual_network.Height[j]) {
                    if (residual_network.Height[j] < min) {
                        min = residual_network.Height[j];
                    }
                }
            }

            // Increase the height of the lowest heighbour plus one
            residual_network.Height[i] = 1 + min;

            return true;
        }
    }
    return false;
}

void PushRelabel::init(Graph &residual_network, int source)
{
    for (int i = 0; i < residual_network.VertexCount; ++i) {
        residual_network.ExcessFlow[i] = 0;
        residual_network.Height[i] = 0;
        residual_network.V[i] = 0;
    }

    residual_network.Height[source] = residual_network.VertexCount;

    for (int i = 0; i < residual_network.VertexCount; ++i) {

        if (residual_network.E[source][i] > 0) {

            int flow = residual_network.E[source][i];

            residual_network.E[i][source] += flow;
            residual_network.E[source][i] -= flow;

            residual_network.ExcessFlow[i] += flow;
            residual_network.ExcessFlow[source] -= flow;
        }
    }
}