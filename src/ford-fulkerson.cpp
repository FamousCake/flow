#include "inc/ford-fulkerson.h"

using namespace std;

FordFulkerson::FordFulkerson(const ResidualNetwork &A) : E(ResidualNetwork(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    // Списък на наследниците, използван от обхождането в ширина
    this->V = vector<int>(VertexCount);

    // Спитък на ребрата, с които се е достигнало до тези наследници
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

// Обхождане на намерения път от източника до шахтата
void FordFulkerson::AugmentPath()
{
    // Намиране на най-лекото ребро по този път
    auto current = A[Sink];

    int min = current->weight;

    while (current != nullptr)
    {
        min = std::min(current->weight, min);

        current = A[current->from];
    }

    // Промяна потока на всички ребра по пътя със стойноста най-лекото
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
