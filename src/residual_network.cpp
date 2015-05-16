#include "./inc/residual_network.h"

using namespace std;

ResidualNetwork::ResidualNetwork(int count, int value, int source, int sink)
{
    this->Count = count;
    this->Source = source;
    this->Sink = sink;

    this->E = new int *[this->Count];
    for (int i = 0; i < this->Count; ++i) {

        this->E[i] = new int[this->Count];

        // Memset is the other alternative but it's not reliable
        std::fill(this->E[i], (this->E[i] + this->Count), value);
    }
}

ResidualNetwork::ResidualNetwork(const std::vector<std::vector<int>> &A, int source, int sink)
{
    this->Count = A.size();
    this->Source = source;
    this->Sink = sink;

    this->E = new int *[this->Count];

    for (int i = 0; i < this->Count; ++i) {

        this->E[i] = new int[this->Count];

        // Not accessing 2D Vector elements like this might yeild better performance, but this part
        // isn't sensitive
        for (int j = 0; j < this->Count; ++j) {
            this->E[i][j] = A[i][j];
        }
    }
}

ResidualNetwork::ResidualNetwork(const ResidualNetwork &A)
{
    this->Count = A.Count;
    this->Source = A.Source;
    this->Sink = A.Sink;

    this->E = new int *[this->Count];
    for (int i = 0; i < this->Count; ++i) {

        this->E[i] = new int[this->Count];

        for (int j = 0; j < this->Count; ++j) {
            this->E[i][j] = A.E[i][j];
        }
    }
}

ResidualNetwork::~ResidualNetwork()
{
    for (int i = 0; i < this->Count; ++i) {
        delete[] this->E[i];
    }

    delete[] this->E;
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

int ResidualNetwork::getSource()
{
    return this->Source;
}

int ResidualNetwork::getSink()
{
    return this->Sink;
}

int **ResidualNetwork::getRaw()
{
    return this->E;
}

void ResidualNetwork::eachEdge(function<void(int, int, int)> callback)
{
    for (int i = 0; i < Count; ++i) {
        for (int j = 0; j < Count; ++j) {
            callback(E[i][j], i, j);
        }
    }
}
