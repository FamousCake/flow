#include "inc/ford-fulkerson.h"

using namespace std;

FordFulkerson::FordFulkerson(const ResidualNetworkMatrix &A) : E(ResidualNetworkMatrix(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->V = new int[VertexCount];
}

FordFulkerson::~FordFulkerson()
{
    delete[] this->V;
}

void FordFulkerson::Run()
{
    while (GetPath())
    {
        AugmentPath();

        this->IterationsCount++;
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

    while (V[x] != x)
    {
        int u = x;
        int v = V[x];

        if (min > E.getWeight(v, u))
        {
            min = E.getWeight(v, u);
        }

        x = V[x];
    }

    //
    // Step 2: Augment every edge on the path by the minimum flow
    //
    x = Sink;
    while (V[x] != x)
    {

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
    std::fill(this->V, this->V + VertexCount, -1);

    SimpleQueue q(VertexCount);
    q.push(Source);

    V[Source] = Source;

    while (q.size() > 0)
    {
        const int u = q.pop();

        for (auto edge : E.getNeighbours(u))
        {
            if (edge.weight != 0 && V[edge.to] == -1)
            {
                q.push(edge.to);

                V[edge.to] = u;

                if (edge.to == Sink)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
