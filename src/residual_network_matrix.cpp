#include "./inc/residual_network_matrix.h"

using namespace std;

ResidualNetworkMatrix::ResidualNetworkMatrix(int count, int value, int source, int sink)
{
    this->Count = count;
    this->Source = source;
    this->Sink = sink;
    this->E = vector<vector<int>>(Count, vector<int>(Count, value));
}

ResidualNetworkMatrix::ResidualNetworkMatrix(const std::vector<std::vector<int>> &A, int source, int sink)
{
    this->Count = A.size();
    this->Source = source;
    this->Sink = sink;
    this->E = vector<vector<int>>(A);
}

ResidualNetworkMatrix::ResidualNetworkMatrix(const ResidualNetworkMatrix &A)
{
    this->Count = A.Count;
    this->Source = A.Source;
    this->Sink = A.Sink;
    this->E = vector<vector<int>>(A.E);
}

ResidualNetworkMatrix::~ResidualNetworkMatrix()
{

}

int ResidualNetworkMatrix::getWeight(int i, int j)
{
    return this->E[i][j];
}

void ResidualNetworkMatrix::setWeight(int i, int j, int w)
{
    this->E[i][j] = w;
}

void ResidualNetworkMatrix::updateWeight(int i, int j, int w)
{
    this->E[i][j] += w;
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
            if (E[i][j] > 0)
            {
                count++;
            }
        }
    }

    return count;
}

int ResidualNetworkMatrix::getSource()
{
    return this->Source;
}

int ResidualNetworkMatrix::getSink()
{
    return this->Sink;
}

vector<vector<int>> ResidualNetworkMatrix::getRaw()
{
    return this->E;
}

void ResidualNetworkMatrix::eachEdge(function<void(int, int, int)> callback)
{
    for (int i = 0; i < Count; ++i)
    {
        for (int j = 0; j < Count; ++j)
        {
            callback(E[i][j], i, j);
        }
    }
}
