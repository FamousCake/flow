#include "./inc/residual_network.h"

using namespace std;

ResidualNetwork::ResidualNetwork(int count, int value)
{
    this->Count = count;
    this->E = new int *[this->Count];

    for (int i = 0; i < this->Count; ++i) {
        this->E[i] = new int[this->Count];
        std::fill(this->E[i], (this->E[i] + this->Count), value);
    }
}

ResidualNetwork::ResidualNetwork(const vector<vector<int>> &v)
{
    cout << v.size();
    this->Count = v.size();

    this->E = new int *[this->Count];

    for (int i = 0; i < this->Count; ++i) {
        this->E[i] = new int[this->Count];

        for (int j = 0; j < this->Count; ++j) {
            this->E[i][j] = v[i][j];
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

int ResidualNetwork::getCount()
{
    return this->Count;
}

int **ResidualNetwork::getRaw()
{
    return this->E;
}
