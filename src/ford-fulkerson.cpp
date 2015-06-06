#include "inc/ford-fulkerson.h"

using namespace std;

FordFulkerson::FordFulkerson(const ResidualNetwork &A) : E(ResidualNetwork(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->V = vector<int>(VertexCount);
    this->A = vector<ResidualEdge *>(VertexCount);
}

FordFulkerson::~FordFulkerson()
{
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
    auto current = A[Sink];

    int min = current->weight;

    while (current != nullptr)
    {
        min = std::min(current->weight, min);

        current = A[current->from];
    }

    current = A[Sink];
    while (current != nullptr)
    {
        current->weight -= min;
        E.getReverseEdge(*current).weight += min;

        current = A[current->from];
    }
}

bool FordFulkerson::GetPath()
{
    queue<int> q;
    vector<bool> V = vector<bool>(VertexCount, false);

    q.push(Source);
    V[Source] = true;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();

        for (auto &edge : E.getOutgoingEdges(u))
        {
            if (edge.weight > 0 && V[edge.to] == false)
            {
                q.push(edge.to);

                V[edge.to] = true;
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
