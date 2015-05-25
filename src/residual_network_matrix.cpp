#include "./inc/residual_network_matrix.h"

using namespace std;

ResidualNetworkMatrix::ResidualNetworkMatrix(int count, int value, int source, int sink)
{
    this->Count = count;
    this->Source = source;
    this->Sink = sink;
    // this->E = vector<vector<pair<int,int>>>(Count, vector<pair<int,int>>(Count, value));
}

ResidualNetworkMatrix::ResidualNetworkMatrix(const std::vector<std::vector<ResidualEdge>> &A, int source, int sink)
{
    this->Count = A.size();
    this->Source = source;
    this->Sink = sink;
    this->E = vector<vector<ResidualEdge>>(A);
}

ResidualNetworkMatrix::ResidualNetworkMatrix(const ResidualNetworkMatrix &A)
{
    this->Count = A.Count;
    this->Source = A.Source;
    this->Sink = A.Sink;
    this->E = vector<vector<ResidualEdge>>(A.E);
}

ResidualNetworkMatrix::~ResidualNetworkMatrix()
{
}

ResidualEdge &ResidualNetworkMatrix::getEdge(int i, int j)
{
    return this->E[i][j];
}

int ResidualNetworkMatrix::getWeight(int i, int j)
{
    return this->E[i][j].weight;
}
void ResidualNetworkMatrix::setWeight(int i, int j, int w)
{
    this->E[i][j].weight = w;
}

void ResidualNetworkMatrix::updateWeight(int i, int j, int w)
{
    this->E[i][j].weight += w;
}

int ResidualNetworkMatrix::getCount()
{
    return this->Count;
}

int ResidualNetworkMatrix::getEdgesCount()
{
    int count = 0;
    for (int i = 0; i < Count; ++i)
    {
        for (int j = 0; j < Count; ++j)
        {
            if (E[i][j].weight > 0)
            {
                count++;
            }
        }
    }

    return count;
}

int ResidualNetworkMatrix::getFlow()
{
    int flow = 0;

    for (auto x : E[Sink])
    {
        if (x.weight > 0)
        {
            flow += x.weight;
        }
    }

    return flow;
}

int ResidualNetworkMatrix::getSource()
{
    return this->Source;
}

int ResidualNetworkMatrix::getSink()
{
    return this->Sink;
}

vector<ResidualEdge> &ResidualNetworkMatrix::getNeighbours(int i)
{
    return this->E[i];
}
