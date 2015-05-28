#include "inc/relabel_to_front.h"

using namespace std;

RelabelToFront::RelabelToFront(const ResidualNetworkList &A) : E(ResidualNetworkList(A))
{
    this->Source = E.getSource();
    this->Sink = E.getSink();
    this->VertexCount = E.getCount();

    this->PushCount = 0;
    this->RelabelCount = 0;
    this->DischargeCount = 0;

    this->V = vector<Vertex>(VertexCount);
    for (int i = 0; i < VertexCount; ++i)
    {
        V[i].NCurrent = E.getNeighbours(i).begin();
    }

    this->HeightCount = vector<int>(2 * VertexCount, 0);

    this->HeightCount[VertexCount] = 1;
    this->HeightCount[0] = VertexCount - 1;

    // The source has a static height of |V|
    V[Source].Height = VertexCount;
}

RelabelToFront::~RelabelToFront()
{
}

void RelabelToFront::Run()
{
    PushInitialFlow();
    SetInitialLabels();

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

    auto begin = E.getNeighbours(i).begin();
    auto end = E.getNeighbours(i).end();
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
        else if (CanPush(*current))
        {
            if (V[j].ExcessFlow == 0 && j != Source && j != Sink)
            {
                ActiveQueue.push(j);
            }
            Push(*current);

            current++;
        }
        else
        {
            current++;
        }
    }

    V[i].NCurrent = current;
}

void RelabelToFront::Push(ResidualEdge &edge)
{
    this->PushCount++;

    int min = std::min(V[edge.from].ExcessFlow, edge.weight);

    // E.getEdge(i, j).weight -= min;
    // E.getEdge(j, i).weight += min;

    edge.weight -= min;
    E.E[edge.to][edge.index].weight +=min;

    V[edge.from].ExcessFlow -= min;
    V[edge.to].ExcessFlow += min;
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

bool RelabelToFront::CanPush(const ResidualEdge &edge)
{
    // 1) Must be overflowing
    if (!IsOverflowing(edge.from))
    {
        return false;
    }

    // 2) There must exist an edge in the residual network
    if (edge.weight == 0)
    {
        return false;
    }

    // 4) i.h = j.h +1
    if (V[edge.from].Height != V[edge.to].Height + 1)
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
    for (int i = 0; i < VertexCount; ++i) {
        V[i].Height = VertexCount;
    }
    V[Sink].Height = 0;

    SimpleQueue q(VertexCount);
    q.push(Sink);

    while (q.size() > 0)
    {
        const int u = q.pop();
        const int dist = V[u].Height + 1;

        // for (int v = 0; v < VertexCount; ++v)
        for ( auto edge : E.getNeighbours(u) )
        {

            if (E.E[edge.to][edge.index].weight > 0 && V[edge.to].Height == VertexCount)
            {
                q.push(edge.to);
                V[edge.to].Height = dist;
            }
        }
    }
}
