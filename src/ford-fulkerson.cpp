#include "inc/ford-fulkerson.h"

using namespace std;

FordFulkerson::FordFulkerson(const ResidualNetwork &A) : E(ResidualNetwork(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->V = new int[VertexCount];
    this->testV = new int[VertexCount];

    for (int i = 0; i < VertexCount; ++i) {
        this->testV[i] = -1;
    }
}

FordFulkerson::~FordFulkerson()
{
    delete[] this->V;
}

void FordFulkerson::Run()
{
    while (GetPath()) {
        AugmentPath();
    }
}

void FordFulkerson::AugmentPath()
{
    //
    // Step 1 : Find the minimum flow the path can be augmented by
    //
    int x = Sink;

    // Let the initial minimum be the first edge on the augmenting path
    int min = E.getWeight(V[x], x);

    while (V[x] != x) {
        int u = x;
        int v = V[x];

        if (min > E.getWeight(v, u)) {
            min = E.getWeight(v, u);
        }

        x = V[x];
    }

    //
    // Step 2: Augment every edge on the path by the minimum flow
    //
    x = Sink;
    while (V[x] != x) {

        int u = x;
        int v = V[x];

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

    SimpleQueue q(VertexCount);
    q.push(Source);

    // The source is the only vertex that is it's own ancestor
    V[Source] = Source;

    while (q.size() > 0) {

        const int u = q.pop();

        for (int v = 0; v < VertexCount; ++v) {

            if (E.getWeight(u, v) != 0 && V[v] == -1) {

                q.push(v);

                V[v] = u;
                testV[v] = 1;

                if (v == Sink) {
                    return true;
                }
            }
        }
    }
    return false;
}
