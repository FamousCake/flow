#include "inc/io.h"

using namespace std;

void IO::printArray(int A[], const char s[], int w, int count)
{
    cout << endl
         << s << endl;

    cout << "Pointer is : " << A << endl;

    for (int i = 0; i < count; ++i) {
        cout << setw(w) << A[i];
    }

    cout << endl;
}

void IO::printResidualNetwork(ResidualNetwork &A, const char s[], int w)
{
    cout << endl
         << s << endl;

    cout << "Pointer is : " << A.getRaw() << endl;

    for (int i = 0; i < A.getCount(); ++i) {
        cout << endl;
        for (int j = 0; j < A.getCount(); ++j) {
            cout << setw(w) << A.getWeight(i, j);
        }
    }

    cout << endl;
}

ResidualNetwork IO::ReadGraph()
{
    char t;
    string s;

    int vertexCount, edgeCount;
    int source, sink;

    vector<vector<int>> E;

    while (cin >> t) {

        if (t == 'c') {
            cin.ignore(256, '\n');
        } else if (t == 'p') {
            cin >> s >> vertexCount >> edgeCount;
            E = vector<vector<int>>(vertexCount, vector<int>(vertexCount, 0));
        } else if (t == 'n') {
            int a;
            char b;
            cin >> a >> b;

            if (b == 's') {
                source = a - 1;
            } else if (b == 't') {
                sink = a - 1;
            }
        } else if (t == 'a') {
            int a, b, c;
            cin >> a >> b >> c;
            E[a - 1][b - 1] = c;
        }
    }

    return ResidualNetwork(E, source, sink);
}
