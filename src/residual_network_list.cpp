#include "./inc/residual_network_list.h"

using namespace std;


ResidualNetworkList::ResidualNetworkList(const vector<vector<pair<int,int>>> &v, int source, int sink)
{
    this->Count = v.size();
    this->Source = source;
    this->Sink = sink;

    this->E = vector<vector<pair<int, int>>>(v);
}

ResidualNetworkList::ResidualNetworkList(const ResidualNetworkList &v)
{
    this->Count = v.Count;
    this->Source = v.Source;
    this->Sink = v.Sink;

    this->E = vector<vector<pair<int, int>>>(v.E);
}

int ResidualNetworkList::getWeight(int i, int j)
{
    int w = -1;

    for(const auto &x : E[i]) {
        if (x.first == j) {
            w = x.second;
        }
    }

    return w;
}

void ResidualNetworkList::setWeight(int i, int j, int w)
{
    for(auto &x : E[i]) {
        if (x.first == j) {
            x.second = w;
        }
    }
}

void ResidualNetworkList::updateWeight(int i, int j, int w)
{
    for(auto &x : E[i]) {
        if (x.first == j) {
            x.second += w;
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
    for(const auto &x : this->E) {
        for(const auto &y : x) {

            if (y.second > 0) {
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

    for(auto x : E[Sink]) {
        flow += x.second;
    }

    return flow;
}

// std::vector<std::pair<int,int>> ResidualNetworkList::getNeighbours(int i)
// {
//     return E[i];
// }
