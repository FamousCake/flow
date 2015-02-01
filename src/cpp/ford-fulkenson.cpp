#include "../inc/ford-fulkerson.h"


Graph FordFulkerson::Run(Graph g)
{

    std::cout << "f ";

     while(GetPath(g,0,4)) {

        AugmentPath(g,0,4);
    }

    std::cout << std::endl;
    io::printGraphEdges(g, 3);

    return g;
}

void FordFulkerson::AugmentPath(Graph &g, int source, int sink)
{
    int min = 100000;

    int x = sink;

    while (g.V[x] != x)
    {
        int u = x;
        int v = g.V[x];

        if ( min > g.E[v][u] ) {
            min = g.E[v][u];
        }

        x = g.V[x];
    }

    x = sink;

    while (g.V[x] != x) {

        int u = x;
        int v = g.V[x];

        g.E[v][u] -= min;
        g.E[u][v] += min;

        x = g.V[x];
    }
}

bool FordFulkerson::GetPath(Graph &g, int source, int sink)
{
    g.ApplyToV( [](int a) -> int { return -1; });

    std::queue<int> q;

    q.push(source);
    g.V[source] = source;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < g.VertexCount; ++v)
        {
            if ( g.E[u][v] != 0 && g.V[v] == -1 ) {
                q.push(v);
                g.V[v] = u;

                if (v == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}