#include "./inc/residual_network.h"

using namespace std;

ResidualNetwork::ResidualNetwork(const vector<vector<ResidualEdge>> &v, int source, int sink)
{
    this->Count = v.size();
    this->Source = source;
    this->Sink = sink;

    this->E = vector<vector<ResidualEdge>>(v);
}

ResidualNetwork::ResidualNetwork(const ResidualNetwork &v)
{
    this->Count = v.Count;
    this->Source = v.Source;
    this->Sink = v.Sink;

    this->E = vector<vector<ResidualEdge>>(v.E);
}

vector<ResidualEdge> &ResidualNetwork::getOutgoingEdges(int i)
{
    return this->E[i];
}

ResidualEdge &ResidualNetwork::getEdge(int i, int j)
{
    int temp = 0;

    for (int z = 0; z < Count; ++z)
    {
        if (E[i][z].to == j)
        {
            temp = z;
            break;
        }
    }

    return E[i][temp];
}

int ResidualNetwork::getCount()
{
    return this->Count;
}

int ResidualNetwork::getEdgesCount()
{
    int s = 0;
    for (const auto &x : this->E)
    {
        for (const auto &y : x)
        {

            if (y.weight > 0)
            {
                s++;
            }
        }
    }
    return s;
}

int ResidualNetwork::getSource()
{
    return this->Source;
}

int ResidualNetwork::getSink()
{
    return this->Sink;
}

int ResidualNetwork::getFlow()
{
    int flow = 0;

    for (auto x : E[Sink])
    {
        flow += x.weight;
    }

    return flow;
}
