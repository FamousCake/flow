#include "inc/relabel_to_front.h"

using namespace std;

void RelabelToFront::Run()
{
    PushInitialFlow();

    // @TODO Think about using forward queue because of all the insertions

    // List of vertices in a topologicaly sorted order of the addmissible network
    // see Introduction, page 749
    vector<int> sortedList;

    for (int i = 0; i < VertexCount; ++i) {
        if (i != Source && i != Sink) {
            sortedList.push_back(i);
        }
    }

    // We iterate from end to begin, because we can only push in the end of a vector, and all other
    // containers are slower to iterate
    vector<int>::reverse_iterator i = sortedList.rbegin();

    do {

        int oldHeight = V[*i].Height;

        Discharge(*i);

        // If the height has changes, we can safely push the vertex onto the back of the
        // topologicaly sorted list
        // see Introduction, page 755
        if (oldHeight < V[*i].Height) {
            sortedList.push_back(*i);
            i = sortedList.rbegin();
        }

        i++;
    } while (i != sortedList.rend());
}

void RelabelToFront::Discharge(int i)
{
    // See Introduction, page 751
    while (V[i].ExcessFlow > 0) {

        auto v = V[i].NCurrent;

        if (v == V[i].Nlist.end()) {
            Relabel(i);
            V[i].NCurrent = V[i].Nlist.begin();
        } else if (CanPush(i, *v)) {
            Push(i, *v);
        } else {
            V[i].NCurrent++;
        }
    }
}

void RelabelToFront::Push(int i, int j)
{
    int min = std::min(V[i].ExcessFlow, E.getWeight(i, j));

    E.updateWeight(i, j, -min);
    E.updateWeight(j, i, min);

    V[i].ExcessFlow -= min;
    V[j].ExcessFlow += min;
}

void RelabelToFront::Relabel(int i)
{
    // If we relabel while discharging we are guaranteed to have at least one neighbour, see
    // Introduction, page 740
    int min = std::numeric_limits<int>::max();

    for (int j = 0; j < VertexCount; ++j) {

        if (E.getWeight(i, j) > 0) {

            if (V[j].Height < min) {
                min = V[j].Height;
            }
        }
    }

    V[i].Height = 1 + min;
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

        if (E.getWeight(Source, i) > 0) {

            int flow = E.getWeight(Source, i);

            E.updateWeight(i, Source, flow);
            E.updateWeight(Source, i, -flow);

            V[i].ExcessFlow += flow;
            V[Source].ExcessFlow -= flow;
        }
    }
}

RelabelToFront::RelabelToFront(const vector<vector<int>> &A, const int source, const int sink)
    : E(ResidualNetwork(A))
{
    this->Sink = sink;
    this->Source = source;
    this->VertexCount = A.size();

    // Initialize vertices properties
    this->V = new Vertex[VertexCount];
    for (int i = 0; i < this->VertexCount; ++i) {
        V[i].Index = i;
        V[i].Height = 0;
        V[i].ExcessFlow = 0;
    }

    // The source has a static height of |V|
    V[Source].Height = VertexCount;

    // Initialize Nlist of every vertix with all edges that can exist in the residual network
    for (int i = 0; i < this->VertexCount; ++i) {
        for (int j = 0; j < this->VertexCount; ++j) {
            if (E.getWeight(i, j) > 0) {

                V[i].Nlist.push_back(j);

                V[j].Nlist.push_back(i);
            }
        }
    }

    // The Nlist iterator always starts at the begining
    for (int i = 0; i < this->VertexCount; ++i) {
        V[i].NCurrent = V[i].Nlist.begin();
    }
}

RelabelToFront::~RelabelToFront()
{
    delete[] V;
}
