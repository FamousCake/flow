#include "inc/push_relabel.h"

void PushRelabel::run(Graph &residual_network, const int s, const int t)
{
    SimpleQueue Q(residual_network.VertexCount);

    PushRelabel::init(residual_network, Q,  s);

    while ( Q.size() > 0 ) {

        std::cout << "blqqqqq - " << Q.front();

        // Pick any active vertex
        int x = Q.front();

        int min = std::numeric_limits<int>::max();

        // For all neighbours
        for (int y = 0; y < residual_network.VertexCount; ++y) {
            if (CanPush(residual_network, x, y)) {

                // If y will be made active with this push (THIS IS THE ONLY PLACE WE PUSH in the Q)
                if (0 == residual_network.ExcessFlow[y] && y != s && y != t) {
                    Q.push(y);
                }

                Push(residual_network, x, y);

                // If the push was saturating X is no longer active!
                if (0 == residual_network.ExcessFlow[x]) {
                    Q.pop();

                    // We can't go on if the vertex is inactive
                    break;
                }
            }
            else if (residual_network.Height[y] < min) {
                min = residual_network.Height[y];
            }
        }

        // If the vertex is still active after going through all the neigbouts
        if (residual_network.ExcessFlow[x] > 0) {
            Relabel(residual_network, x, min);

        }
    }
}


bool PushRelabel::CanPush(Graph &residual_network, const int x, const int y)
{
    return residual_network.E[x][y] > 0 && residual_network.Height[x] == (residual_network.Height[y] + 1);
}

void PushRelabel::Push(Graph &residual_network, const int x, const int y)
{
    int min = std::min(residual_network.ExcessFlow[x], residual_network.E[x][y]);

    residual_network.E[x][y] -= min;
    residual_network.E[y][x] += min;

    residual_network.ExcessFlow[x] -= min;
    residual_network.ExcessFlow[y] += min;
}

void PushRelabel::Relabel(Graph &residual_network, const int x, const int min)
{
    // Increase the height of the lowest heighbour plus one
    residual_network.Height[x] = 1 + min;
}


void PushRelabel::init(Graph &residual_network, SimpleQueue &Q, int source)
{
    for (int i = 0; i < residual_network.VertexCount; ++i) {
        residual_network.ExcessFlow[i] = 0;
        residual_network.Height[i] = 0;
        residual_network.V[i] = 0;
    }

    residual_network.Height[source] = residual_network.VertexCount;

    for (int i = 0; i < residual_network.VertexCount; ++i) {

        if (residual_network.E[source][i] > 0) {

            int flow = residual_network.E[source][i];

            residual_network.E[i][source] += flow;
            residual_network.E[source][i] -= flow;

            residual_network.ExcessFlow[i] += flow;
            residual_network.ExcessFlow[source] -= flow;

            Q.push(i);
        }
    }
}