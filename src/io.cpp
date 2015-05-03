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

vector<vector<int>> IO::ReadGraph(const char filename[])
{
    ifstream myfile(filename);

    if (!myfile.is_open()) {
        return vector<vector<int>>();
    }

    int vertexCount;
    myfile >> vertexCount;

    vector<vector<int>> E(vertexCount, vector<int>(vertexCount, 0));

    for (int i = 0; i < vertexCount; ++i) {

        for (int j = 0; j < vertexCount; ++j) {
            int w;
            myfile >> w;
            E[i][j] = w;
        }
    }

    myfile.close();

    return E;
}
