#include "inc/ford-fulkerson.h"

FordFulkerson::FordFulkerson(int A[][Globals::MaxGraphSize], const int count, const int source,
                             const int sink)
{
    this->Sink = sink;
    this->Source = source;
    this->VertexCount = count;

    // Copy the residual network
    for (int i = 0; i < this->VertexCount; ++i) {
        for (int j = 0; j < this->VertexCount; ++j) {
            this->E[i][j] = A[i][j];
        }
    }
}

void FordFulkerson::Run()
{
    while (GetPath()) {
        AugmentPath();
    }
}

void FordFulkerson::AugmentPath()
{
    // Step 1 : Find the minimum flow the path can be augmented by
    int x = Sink;
    int min = E[V[x]][x];

    while (V[x] != x) {
        int u = x;
        int v = V[x];

        if (min > E[v][u]) {
            min = E[v][u];
        }

        x = V[x];
    }

    // Step 2: Augment every edge on the path by the minimum flow
    x = Sink;
    while (V[x] != x) {

        int u = x;
        int v = V[x];

        E[v][u] -= min;
        E[u][v] += min;

        x = V[x];
    }
}

bool FordFulkerson::GetPath()
{
    // Reset the list of ancestors for every BFS search
    for (int i = 0; i < VertexCount; ++i) {
        V[i] = -1;
    }

    SimpleQueue q(VertexCount);
    q.push(Source);

    // The source is the only vertex that is it's own ancestor
    V[Source] = Source;

    while (q.size() > 0) {

        const int u = q.pop();

        for (int v = 0; v < VertexCount; ++v) {

            // Is there is an edge and V has not yet been discovered
            if (E[u][v] != 0 && V[v] == -1) {

                q.push(v);

                V[v] = u;

                if (v == Sink) {
                    return true;
                }
            }
        }
    }

    return false;
}
