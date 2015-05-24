#include "./inc/residual_network.h"

using namespace std;

ResidualNetwork::ResidualNetwork(int count, int value, int source, int sink)
{
    this->Count = count;
    this->Source = source;
    this->Sink = sink;
    this->E = vector<vector<int>>(Count, vector<int>(Count, value));
}

ResidualNetwork::ResidualNetwork(const std::vector<std::vector<int>> &A, int source, int sink)
{
    this->Count = A.size();
    this->Source = source;
    this->Sink = sink;
    this->E = vector<vector<int>>(A);
}

ResidualNetwork::ResidualNetwork(const ResidualNetwork &A)
{
    this->Count = A.Count;
    this->Source = A.Source;
    this->Sink = A.Sink;
    this->E = vector<vector<int>>(A.E);
}

int ResidualNetwork::getWeight(int i, int j)
{
    return this->E[i][j];
}

void ResidualNetwork::setWeight(int i, int j, int w)
{
    this->E[i][j] = w;
}

void ResidualNetwork::updateWeight(int i, int j, int w)
{
    this->E[i][j] += w;
}

int ResidualNetwork::getCount()
{
    return this->Count;
}

int ResidualNetwork::getEdgesCount()
{
    int count = 0;
    for (int i = 0; i < Count; ++i)
    {
        for (int j = 0; j < Count; ++j)
        {
            if (E[i][j] > 0)
            {
                count++;
            }
        }
    }

    return count;
}

int ResidualNetwork::getSource()
{
    return this->Source;
}

int ResidualNetwork::getSink()
{
    return this->Sink;
}

vector<vector<int>> ResidualNetwork::getRaw()
{
    return this->E;
}

void ResidualNetwork::eachEdge(function<void(int, int, int)> callback)
{
    for (int i = 0; i < Count; ++i)
    {
        for (int j = 0; j < Count; ++j)
        {
            callback(E[i][j], i, j);
        }
    }
}
