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

int ResidualNetworkList::getWeight(int i, int j)
{
    int w = -1;

    for (const auto &x : E[i])
    {
        if (x.to == j)
        {
            w = x.weight;
        }
    }

    return w;
}

void ResidualNetworkList::setWeight(int i, int j, int w)
{
    for (auto &x : E[i])
    {
        if (x.to == j)
        {
            x.weight = w;
        }
    }
}

void ResidualNetworkList::updateWeight(int i, int j, int w)
{
    for (auto &x : E[i])
    {
        if (x.to == j)
        {
            x.weight += w;
        }
    }
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

vector<ResidualEdge> &ResidualNetworkList::getNeighbours(int i)
{
    return this->E[i];
}
