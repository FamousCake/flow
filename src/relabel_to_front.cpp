#include "inc/relabel_to_front.h"

void RelabelToFront::Run()
{
    PushInitialFlow();

    int current = -1;

    // @TODO Make this use a linked list
    do {
        current = FindOverflowing();

        if (current != -1) {
            Discharge(current);
        }

    } while (current != -1);
}

void RelabelToFront::Discharge(int i)
{
    // u is active, doesn't matter what the others are!
    // @TODO Make this a list as well
    while (V[i].ExcessFlow > 0) {

        if (CanRelabel(i)) {
            Relabel(i);
        }

        for (int j = 0; j < VertexCount; ++j) {
            if (CanPush(i, j)) {
                Push(i, j);
            }
        }
    }
}

// @TODO Get rid of this entirely
int RelabelToFront::FindOverflowing()
{
    for (int i = 0; i < VertexCount; ++i) {
        if (IsOverflowing(i)) {
            return i;
        }
    }

    return -1;
}

void RelabelToFront::Push(int i, int j)
{
    int min = std::min(V[i].ExcessFlow, E[i][j]);

    E[i][j] -= min;
    E[j][i] += min;

    V[i].ExcessFlow -= min;
    V[j].ExcessFlow += min;
}

void RelabelToFront::Relabel(int i)
{
    int min = std::numeric_limits<int>::max();

    for (int j = 0; j < VertexCount; ++j) {

        if (E[i][j] > 0) {

            if (V[j].Height < min) {
                min = V[j].Height;
            }
        }
    }

    V[i].Height = 1 + min;
}

bool RelabelToFront::CanPush(int i, int j)
{
    // i must be overflowing
    if (!IsOverflowing(i)) {
        return false;
    }

    // 2) There must exist an edge in the residual network
    if (E[i][j] == 0) {
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
    // i must be overflowing
    if (!IsOverflowing(i)) {
        return false;
    }

    // All neigbors must be highter than i
    for (int j = 0; j < VertexCount; ++j) {
        if (E[i][j] > 0) {
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
    // Pushing the first flow to the neighbours of the Source
    for (int i = 0; i < VertexCount; ++i) {

        if (E[Source][i] > 0) {

            // Push the capasity of the edge
            int flow = E[Source][i];

            E[i][Source] += flow;
            E[Source][i] -= flow;

            V[i].ExcessFlow += flow;
            V[Source].ExcessFlow -= flow;
        }
    }
}

RelabelToFront::RelabelToFront(int A[][MAX_GRAPH_SIZE], const int count, const int source,
                               const int sink)
{
    this->Sink = sink;
    this->Source = source;
    this->VertexCount = count;

    // Initialize all the new vertices
    for (int i = 0; i < this->VertexCount; ++i) {
        V[i].Index = i;
        V[i].Height = 0;
        V[i].ExcessFlow = 0;
        V[i].Current = 0;
        V[i].NCount = 0;
    }

    // Copy the residual network and make the possible neigbor lists
    for (int i = 0; i < this->VertexCount; ++i) {
        for (int j = 0; j < this->VertexCount; ++j) {

            this->E[i][j] = A[i][j];

            // If (i,j) e E, then both (i, j) and (j, i) can appear in the residual network
            if (A[i][j] > 0) {

                V[i].NList[V[i].Current] = j;
                V[i].Current++;

                V[j].NList[V[j].Current] = i;
                V[j].Current++;
            }
        }
    }

    // Set current to the start of the list and remember the count
    for (int i = 0; i < this->VertexCount; ++i) {
        V[i].NCount = V[i].Current;
        V[i].Current = 0;
    }

    V[Source].Height = VertexCount;
}

RelabelToFront::~RelabelToFront()
{
}
