#include "inc/push_relabel.h"

void PushRelabel::run(Graph &residual_network, const int s, const int t)
{
    PushRelabel::init(residual_network, s);

    while (true) {
        int current = FindOverflowing(residual_network, s, t);

        if (current == -1) {
            break;
        } else {
            Discharge(residual_network, current);
        }
    }
}

void PushRelabel::Discharge(Graph &residual_network, int i)
{
    // u is active, doesn't matter what the others are!
    while (residual_network.ExcessFlow[i] > 0) {

        // If you can relabel, go ahead
        if (CanRelabel(residual_network, i)) {
            Relabel(residual_network, i);
        }

        // Push to all neighbours
        for (int j = 0; j < residual_network.VertexCount; ++j) {
            if (residual_network.E[i][j] > 0) {
                if (CanPush(residual_network, i, j)) {
                    Push(residual_network, i, j);
                }
            }
        }
    }
}

int PushRelabel::FindOverflowing(Graph &residual_network, int s, int t)
{
    for (int i = 0; i < residual_network.VertexCount; ++i) {
        if (i != s && i != t && residual_network.ExcessFlow[i] > 0) {
            return i;
        }
    }

    return -1;
}

// Pushing
bool PushRelabel::CanPush(Graph &residual_network, int i, int j)
{
    // 1) Vertex i must be overflowing
    if (residual_network.ExcessFlow[i] == 0) {
        return false;
    }

    // 2) The must exist an edge in the residual network
    if (residual_network.E[i][j] == 0) {
        return false;
    }

    // 4) i.h = j.h +1
    if (residual_network.Height[i] != residual_network.Height[j] + 1) {
        return false;
    }

    return true;
}

void PushRelabel::Push(Graph &residual_network, const int i, const int j)
{
    int min = std::min(residual_network.ExcessFlow[i], residual_network.E[i][j]);

    residual_network.E[i][j] -= min;
    residual_network.E[j][i] += min;

    residual_network.ExcessFlow[i] -= min;
    residual_network.ExcessFlow[j] += min;
}

// Relabeling
bool PushRelabel::CanRelabel(Graph &residual_network, const int i)
{
    // i must be overflowing
    if (residual_network.ExcessFlow[i] == 0) {
        return false;
    }

    // All neighbours of u must be at the same height or heigher
    for (int j = 0; j < residual_network.VertexCount; ++j) {
        if (residual_network.Height[i] > residual_network.Height[j]) {
            return false;
        }
    }

    return true;
}

void PushRelabel::Relabel(Graph &residual_network, int i)
{
    int min = std::numeric_limits<int>::max();

    for (int j = 0; j < residual_network.VertexCount; ++j) {

        if (residual_network.E[i][j] > 0) {

            if (residual_network.Height[j] < min) {
                min = residual_network.Height[j];
            }
        }
    }

    residual_network.Height[i] = 1 + min;
}

// Initialization
void PushRelabel::init(Graph &residual_network, int source)
{
    // Making sure initial values are valied
    for (int i = 0; i < residual_network.VertexCount; ++i) {
        residual_network.ExcessFlow[i] = 0;
        residual_network.Height[i] = 0;
        residual_network.V[i] = 0;
    }

    // Height of the source is |V|
    residual_network.Height[source] = residual_network.VertexCount;

    // Pushing the first flow to the neighbours of the source
    for (int i = 0; i < residual_network.VertexCount; ++i) {

        if (residual_network.E[source][i] > 0) {

            // Push the capasity of the edge
            int flow = residual_network.E[source][i];

            residual_network.E[i][source] += flow;
            residual_network.E[source][i] -= flow;

            residual_network.ExcessFlow[i] += flow;
            residual_network.ExcessFlow[source] -= flow;
        }
    }
}