#include "inc/relabel_to_front.h"

using namespace std;

void RelabelToFront::Run()
{
    PushInitialFlow();

    this->GetPath();

    for (int i = 0; i < VertexCount; ++i)
    {
        if (i != Source && i != Sink)
        {
            Q.push(i);
        }
    }

    do
    {
        int i = Q.front();
        Q.pop();

        Discharge(i);

    } while (!Q.empty());
}

void RelabelToFront::Discharge(int i)
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
                Q.push(j);
            }
            Push(i, j);
        }
        else
        {
            current++;
        }
    }

    V[i].NCurrent = current;
}

void RelabelToFront::Push(int i, int j)
{
    this->PushCount++;
    this->V[i].PushCount++;

    int min = std::min(V[i].ExcessFlow, E.getEdge(i, j).weight);

    E.getEdge(i, j).weight -= min;
    E.getEdge(j, i).weight += min;

    V[i].ExcessFlow -= min;
    V[j].ExcessFlow += min;
}

void RelabelToFront::Relabel(int i)
{
    this->RelabelCount++;
    this->V[i].RelabelCount++;

    auto minHeight = 2 * VertexCount;
    for (auto edge : E.getNeighbours(i))
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

void RelabelToFront::Gap(int k)
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

bool RelabelToFront::CanPush(int i, int j)
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

bool RelabelToFront::CanRelabel(int i)
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

bool RelabelToFront::IsOverflowing(int i)
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

RelabelToFront::RelabelToFront(const ResidualNetworkMatrix &A) : E(ResidualNetworkMatrix(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->PushCount = 0;
    this->RelabelCount = 0;
    this->DischargeCount = 0;

    // Initialize vertices properties
    this->V = new Vertex[VertexCount];
    for (int i = 0; i < VertexCount; ++i)
    {
        V[i].NCurrent = E.getNeighbours(i).cbegin();
    }

    this->HeightCount = new int[2 * VertexCount];

    std::fill(this->HeightCount, (this->HeightCount + 2 * VertexCount), 0);
    this->HeightCount[VertexCount] = 1;
    this->HeightCount[0] = VertexCount - 1;

    // The source has a static height of |V|
    V[Source].Height = VertexCount;

    // Initialize NList of every vertix with all edges that can exist in the residual network
    // for (int i = 0; i < this->VertexCount; ++i)
    // {
    //     for (int j = 0; j < this->VertexCount; ++j)
    //     {
    //         if (E.getWeight(i, j) > 0)
    //         {
    //
    //             V[i].NList.push_back(j);
    //
    //             V[j].NList.push_back(i);
    //         }
    //     }
    // }
    //
    // // The NList iterator always starts at the begining
    // for (int i = 0; i < this->VertexCount; ++i)
    // {
    //     V[i].NCurrent = V[i].NList.begin();
    // }
}

RelabelToFront::~RelabelToFront()
{
    delete[] V;
    delete[] HeightCount;
}

void RelabelToFront::GetPath()
{
    bool *A = new bool[VertexCount];
    // Reset the list of ancestors for every BFS search
    for (int i = 0; i < VertexCount; ++i)
    {
        A[i] = false;

        if (i != Sink && i != Source)
        {
            // V[i].Height = VertexCount;
        }
    }

    SimpleQueue q(VertexCount);
    q.push(Sink);

    // The source is the only vertex that is it's own ancestor
    A[Sink] = true;

    while (q.size() > 0)
    {
        const int u = q.pop();
        int dist = V[u].Height + 1;

        for (int v = 0; v < VertexCount; ++v)
        {
            if (E.getEdge(v, u).weight > 0 && A[v] == false && v != Source)
            {
                q.push(v);

                A[v] = true;
                V[v].Height = dist;
            }
        }
    }
}
