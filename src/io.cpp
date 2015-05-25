#include "inc/io.h"

using namespace std;

void IO::printArray(int A[], int count, int w, const char msg[])
{
    cout << '\n' << msg << '\n';

    cout << "Pointer is : " << A << endl;

    for (int i = 0; i < count; ++i)
    {
        cout << setw(w) << A[i];
    }

    cout << endl;
}

void IO::printResidualNetwork(ResidualNetwork &A, int w, const char msg[])
{
    cout << '\n' << msg << '\n';

    cout << "Pointer is : " << &A << endl;

    for (int i = 0; i < A.getCount(); ++i)
    {
        cout << endl;
        for (int j = 0; j < A.getCount(); ++j)
        {
            cout << setw(w) << A.getWeight(i, j);
        }
    }

    cout << endl;
}

ResidualNetworkMatrix IO::ReadGraph()
{
    char t;

    int vertexCount, edgeCount;
    int source, sink;

    vector<vector<ResidualEdge>> E;

    while (cin >> t)
    {

        if (t == 'c')
        {
            cin.ignore(256, '\n');
        }
        else if (t == 'p')
        {
            string s;
            cin >> s >> vertexCount >> edgeCount;
            E = vector<vector<ResidualEdge>>(vertexCount, vector<ResidualEdge>(vertexCount, ResidualEdge(-1, -1, -1)));
        }
        else if (t == 'n')
        {
            int a;

            char b;
            cin >> a >> b;

            if (b == 's')
            {
                source = a - 1;
            }
            else if (b == 't')
            {
                sink = a - 1;
            }
        }
        else if (t == 'a')
        {
            int a, b, c;
            cin >> a >> b >> c;

            // E[a-1][b-1] = Edge(a-1, b-1, c);

            E[a - 1][b - 1].from = a - 1;
            E[a - 1][b - 1].to = b - 1;
            E[a - 1][b - 1].weight = c;

            E[b - 1][a - 1].from = b - 1;
            E[b - 1][a - 1].to = a - 1;
            E[b - 1][a - 1].weight = 0;
        }
    }

    return ResidualNetworkMatrix(E, source, sink);
}

ResidualNetworkList IO::ReadGraphList()
{
    char t;

    int vertexCount, edgeCount;
    int source, sink;

    vector<vector<ResidualEdge>> E;

    while (cin >> t)
    {

        if (t == 'c')
        {
            cin.ignore(256, '\n');
        }
        else if (t == 'p')
        {
            string s;
            cin >> s >> vertexCount >> edgeCount;
            E = vector<vector<ResidualEdge>>(vertexCount, vector<ResidualEdge>());
        }
        else if (t == 'n')
        {
            int a;
            char b;
            cin >> a >> b;

            if (b == 's')
            {
                source = a - 1;
            }
            else if (b == 't')
            {
                sink = a - 1;
            }
        }
        else if (t == 'a')
        {
            int a, b, c;
            cin >> a >> b >> c;
            // E[a - 1][b - 1] = c;
            E[a - 1].push_back(ResidualEdge(a-1, b - 1, c));
            E[b - 1].push_back(ResidualEdge(b-1, a - 1, 0));
        }
    }

    return ResidualNetworkList(E, source, sink);
}

void IO::WriteGraph(ResidualNetwork &E)
{
    int edgeCount = 0;

    for (int i = 0; i < E.getCount(); ++i)
    {
        for (int j = 0; j < E.getCount(); ++j)
        {
            if (E.getWeight(i, j))
            {
                edgeCount++;
            }
        }
    }

    cout << "c" << endl;
    cout << "c This is a generated graph" << endl;
    cout << "c" << endl;
    cout << "p max " << E.getCount() << " " << edgeCount << endl;
    cout << "n " << E.getSource() + 1 << " s" << endl;
    cout << "n " << E.getSink() + 1 << " t" << endl;

    for (int i = 0; i < E.getCount(); ++i)
    {
        for (int j = 0; j < E.getCount(); ++j)
        {
            if (E.getWeight(i, j))
            {
                cout << "a " << i + 1 << " " << j + 1 << " " << E.getWeight(i, j) << endl;
            }
        }
    }

    cout << "c End of file;";
}
