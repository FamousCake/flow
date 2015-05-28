#include "./inc/residual_network_list.h"

using namespace std;

ResidualNetworkList::ResidualNetworkList(const vector<vector<ResidualEdge>> &v, int source, int sink)
{
    this->Count = v.size();
    this->Source = source;
    this->Sink = sink;

    this->E = vector<vector<ResidualEdge>>(v);
}

ResidualNetworkList::ResidualNetworkList(const ResidualNetworkList &v)
{
    this->Count = v.Count;
    this->Source = v.Source;
    this->Sink = v.Sink;

    this->E = vector<vector<ResidualEdge>>(v.E);
}

ResidualEdge &ResidualNetworkList::getEdge(int i, int j)
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

int ResidualNetworkList::getCount()
{
    return this->Count;
}

int ResidualNetworkList::getEdgesCount()
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

int ResidualNetworkList::getSource()
{
    return this->Source;
}

int ResidualNetworkList::getSink()
{
    return this->Sink;
}

int ResidualNetworkList::getFlow()
{
    int flow = 0;

    for (auto x : E[Sink])
    {
        flow += x.weight;
    }

    return flow;
}

vector<ResidualEdge> &ResidualNetworkList::getOutgoingEdges(int i)
{
    return this->E[i];
}
