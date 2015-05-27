#include "inc/relabel_to_front.h"

using namespace std;

RelabelToFront::RelabelToFront(const ResidualNetworkMatrix &A) : E(ResidualNetworkMatrix(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->PushCount = 0;
    this->RelabelCount = 0;
    this->DischargeCount = 0;

    this->A = new bool[VertexCount];

    this->V = vector<Vertex>(VertexCount);
    for (int i = 0; i < VertexCount; ++i)
    {
        V[i].NCurrent = E.getNeighbours(i).cbegin();
    }

    this->HeightCount = vector<int>(2 * VertexCount, 0);

    this->HeightCount[VertexCount] = 1;
    this->HeightCount[0] = VertexCount - 1;

    // The source has a static height of |V|
    V[Source].Height = VertexCount;
}

RelabelToFront::~RelabelToFront()
{
    delete[] A;
}

void RelabelToFront::Run()
{
    PushInitialFlow();
    // SetInitialLabels();

    for (int i = 0; i < VertexCount; ++i)
    {
        if (i != Source && i != Sink)
        {
            ActiveQueue.push(i);
        }
    }

    do
    {
        int i = ActiveQueue.front();
        ActiveQueue.pop();

        Discharge(i);

    } while (!ActiveQueue.empty());
}

void RelabelToFront::Discharge(const int i)
{
    this->DischargeCount++;

    auto begin = E.getNeighbours(i).cbegin();
    auto end = E.getNeighbours(i).cend();
    auto current = V[i].NCurrent;

    while (V[i].ExcessFlow > 0)
    {
        int j = (*current).to;

        if (current == end)
        {
            int oldHeight = V[i].Height;

            Relabel(i);

            // We have a gap
            if (HeightCount[oldHeight] == 0)
            {
                Gap(oldHeight);
            }

            current = begin;
        }
        else if (CanPush(i, j))
        {
            if (V[j].ExcessFlow == 0 && j != Source && j != Sink)
            {
                ActiveQueue.push(j);
            }
            Push(i, j);

            current++;
        }
        else
        {
            current++;
        }
    }

    V[i].NCurrent = current;
}

void RelabelToFront::Push(const int i, const int j)
{
    this->PushCount++;
    this->V[i].PushCount++;

    int min = std::min(V[i].ExcessFlow, E.getEdge(i, j).weight);

    E.getEdge(i, j).weight -= min;
    E.getEdge(j, i).weight += min;

    V[i].ExcessFlow -= min;
    V[j].ExcessFlow += min;
}

void RelabelToFront::Relabel(const int i)
{
    this->RelabelCount++;
    this->V[i].RelabelCount++;

    auto minHeight = 2 * VertexCount;
    for (const auto &edge : E.getNeighbours(i))
    {
        if (edge.weight > 0)
        {
            minHeight = min(minHeight, V[edge.to].Height);
        }
    }

    HeightCount[V[i].Height]--;
    V[i].Height = minHeight + 1;
    HeightCount[V[i].Height]++;
}

void RelabelToFront::Gap(const int k)
{
    for (int i = 0; i < VertexCount; i++)
    {
        if (i != Source && i != Sink && V[i].Height >= k)
        {
            HeightCount[V[i].Height]--;
            V[i].Height = std::max(V[i].Height, VertexCount + 1);
            HeightCount[V[i].Height]++;
        }
    }
}

bool RelabelToFront::CanPush(const int i, const int j)
{
    // 1) Must be overflowing
    if (!IsOverflowing(i))
    {
        return false;
    }

    // 2) There must exist an edge in the residual network
    if (E.getWeight(i, j) == 0)
    {
        return false;
    }

    // 4) i.h = j.h +1
    if (V[i].Height != V[j].Height + 1)
    {
        return false;
    }

    return true;
}

bool RelabelToFront::CanRelabel(const int i)
{
    // 1) Must be overflowing
    if (!IsOverflowing(i))
    {
        return false;
    }

    // 2) All neigbors must be highter
    for (int j = 0; j < VertexCount; ++j)
    {
        if (E.getWeight(i, j) > 0)
        {
            if (V[i].Height > V[j].Height)
            {
                return false;
            }
        }
    }

    return true;
}

bool RelabelToFront::IsOverflowing(const int i)
{
    return V[i].ExcessFlow > 0 && i != Source && i != Sink;
}

void RelabelToFront::PushInitialFlow()
{
    // Push the capacity of the cut {s, V-s}
    for (int i = 0; i < VertexCount; ++i)
    {
        int capacity = E.getWeight(Source, i);

        if (capacity > 0)
        {
            E.updateWeight(i, Source, capacity);
            E.updateWeight(Source, i, -capacity);

            V[i].ExcessFlow += capacity;
            V[Source].ExcessFlow -= capacity;
        }
    }
}

void RelabelToFront::SetInitialLabels()
{
    std::fill(this->A, this->A + VertexCount, false);

    A[Sink] = true;
    A[Source] = true;

    SimpleQueue q(VertexCount);
    q.push(Sink);

    while (q.size() > 0)
    {
        const int u = q.pop();
        const int dist = V[u].Height + 1;

        for (int v = 0; v < VertexCount; ++v)
        {
            if (E.getEdge(v, u).weight > 0 && A[v] == false)
            {
                q.push(v);
                A[v] = true;
                V[v].Height = dist;
            }
        }
    }
}
