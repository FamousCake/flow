#include "inc/ford-fulkerson.h"

using namespace std;

FordFulkerson::FordFulkerson(const ResidualNetworkList &A) : E(ResidualNetworkList(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->V = vector<int>(VertexCount);
    this->A = vector<ResidualEdge *>(VertexCount);
}

FordFulkerson::~FordFulkerson()
{
    // DON'T DO THIS!
    // std::for_each(A.begin(), A.end(), [](ResidualEdge const *ptr) { delete ptr;});
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
    int x = Sink;

    int min = A[x]->weight;

    while (V[x] != x)
    {
        min = std::min(A[x]->weight, min);

        x = V[x];
    }

    x = Sink;
    while (V[x] != x)
    {
        A[x]->weight -= min;
        E.E[x][A[x]->index].weight += min;

        x = V[x];
    }
}

bool FordFulkerson::GetPath()
{
    std::fill(this->V.begin(), this->V.end(), -1);

    SimpleQueue q(VertexCount);
    q.push(Source);

    V[Source] = Source;

    while (q.size() > 0)
    {
        const int u = q.pop();

        for (auto &edge : E.getOutgoingEdges(u))
        {
            if (edge.weight > 0 && V[edge.to] == -1)
            {
                q.push(edge.to);

                V[edge.to] = u;
                A[edge.to] = &edge;

                if (edge.to == Sink)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
