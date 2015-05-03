#include "inc/ford-fulkerson.h"

using namespace std;

FordFulkerson::FordFulkerson(const vector<vector<int>> &raw, const int source,
                             const int sink) : E(ResidualNetwork(raw)), Source(source), Sink(sink)
{
    this->VertexCount = raw.size();
}

int FordFulkerson::GetFlow()
{
    int s = 0;
    for (int i = 0; i < VertexCount; ++i) {
        // s += E[Sink][i];
        s += E.getWeight(Sink, i);
    }

    return s;
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

    // Let the initial minimum be the first edge on the augmenting path

    // int min = E[V[x]][x];
    int min = E.getWeight(V[x], x);

    while (V[x] != x) {
        int u = x;
        int v = V[x];

        // if (min > E[v][u]) {
            // min = E[v][u];
        // }

        if (min > E.getWeight(v, u)) {
            min = E.getWeight(v, u);
        }

        x = V[x];
    }

    // Step 2: Augment every edge on the path by the minimum flow
    x = Sink;
    while (V[x] != x) {

        int u = x;
        int v = V[x];

        // E[v][u] -= min;
        // E[u][v] += min;

        E.updateWeight(v, u, -min);
        E.updateWeight(u, v, min);

        x = V[x];
    }
}

bool FordFulkerson::GetPath()
{
    // Reset the list of ancestors for every BFS search
    for (int i = 0; i < VertexCount; ++i) {
        V[i] = -1;
    }

    cout << VertexCount;

    SimpleQueue q(VertexCount);
    q.push(Source);

    // The source is the only vertex that is it's own ancestor
    V[Source] = Source;

    while (q.size() > 0) {

        const int u = q.pop();

        for (int v = 0; v < VertexCount; ++v) {

            // Is there is an edge and V has not yet been discovered

            // if (E[u][v] != 0 && V[v] == -1) {
            if (E.getWeight(u, v) != 0 && V[v] == -1) {

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
