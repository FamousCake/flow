#include "inc/relabel_to_front.h"

using namespace std;

void RelabelToFront::Run()
{
    PushInitialFlow();

    int *list = new int[VertexCount];
    int current = 0;

    for (int i = 1; i < VertexCount - 1; ++i) {
        if (i != Source && i != Sink) {
            list[current++] = i;
        }
    }

    current = 0;

    do {

        int i = list[current];

        if (V[i].ExcessFlow > 0) {
            int oldHeight = V[i].Height;

            Discharge(i);

            if (oldHeight < V[i].Height) {
                swap(list[current], list[0]);
                current = 0;
            }
        }

        current++;
    } while (current != VertexCount - 2);

    delete[] list;
}

void RelabelToFront::Discharge(int i)
{
    this->DischargeCount++;

    // See Introduction, page 751
    while (V[i].ExcessFlow > 0) {

        auto v = V[i].NCurrent;

        if (v == V[i].NList.end()) {
            Relabel(i);
            V[i].NCurrent = V[i].NList.begin();
        } else if (CanPush(i, *v)) {
            Push(i, *v);
        } else {
            V[i].NCurrent++;
        }
    }
}

void RelabelToFront::Push(int i, int j)
{
    this->PushCount++;
    this->V[i].PushCount++;

    int min = std::min(V[i].ExcessFlow, E.getWeight(i, j));

    E.updateWeight(i, j, -min);
    E.updateWeight(j, i, min);

    V[i].ExcessFlow -= min;
    V[j].ExcessFlow += min;
}

void RelabelToFront::Relabel(int i)
{
    this->RelabelCount++;
    this->V[i].RelabelCount++;

    V[i].Height = 2 * VertexCount;

    for (auto j : V[i].NList) {
        if (E.getWeight(i, j) > 0) {
            V[i].Height = min(V[i].Height, V[j].Height);
        }
    }

    V[i].Height++;
}

bool RelabelToFront::CanPush(int i, int j)
{
    // 1) Must be overflowing
    if (!IsOverflowing(i)) {
        return false;
    }

    // 2) There must exist an edge in the residual network
    if (E.getWeight(i, j) == 0) {
        return false;
    }

    // 4) i.h = j.h +1
    if (V[i].Height != V[j].Height + 1) {
        return false;
    }

    return true;
}

bool RelabelToFront::CanRelabel(int i)
{
    // 1) Must be overflowing
    if (!IsOverflowing(i)) {
        return false;
    }

    // 2) All neigbors must be highter
    for (int j = 0; j < VertexCount; ++j) {
        if (E.getWeight(i, j) > 0) {
            if (V[i].Height > V[j].Height) {
                return false;
            }
        }
    }

    return true;
}

bool RelabelToFront::IsOverflowing(int i)
{
    return V[i].ExcessFlow > 0 && i != Source && i != Sink;
}

void RelabelToFront::PushInitialFlow()
{
    // Push the capacity of the edge for every (Source, i) e E
    for (int i = 0; i < VertexCount; ++i) {

        int flow = E.getWeight(Source, i);

        if (flow > 0) {

            E.updateWeight(i, Source, flow);
            E.updateWeight(Source, i, -flow);

            V[i].ExcessFlow += flow;
            V[Source].ExcessFlow -= flow;
        }
    }
}

RelabelToFront::RelabelToFront(const ResidualNetwork &A) : E(ResidualNetwork(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->PushCount = 0;
    this->RelabelCount = 0;
    this->DischargeCount = 0;

    // Initialize vertices properties
    this->V = new Vertex[VertexCount];
    for (int i = 0; i < this->VertexCount; ++i) {
        V[i].Index = i;
        V[i].Height = 0;
        V[i].ExcessFlow = 0;
    }

    // The source has a static height of |V|
    V[Source].Height = VertexCount;

    // Initialize NList of every vertix with all edges that can exist in the residual network
    for (int i = 0; i < this->VertexCount; ++i) {
        for (int j = 0; j < this->VertexCount; ++j) {
            if (E.getWeight(i, j) > 0) {

                V[i].NList.push_back(j);

                V[j].NList.push_back(i);
            }
        }
    }

    // The NList iterator always starts at the begining
    for (int i = 0; i < this->VertexCount; ++i) {
        V[i].NCurrent = V[i].NList.begin();
    }
}

RelabelToFront::~RelabelToFront()
{
    delete[] V;
}
