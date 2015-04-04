#include "inc/io.h"

using namespace std;

void IO::printArray(int A[], const char s[], int w, int count)
{
    cout << endl
         << s;

    cout << "Pointer is : " << A << endl;

    for (int i = 0; i < count; ++i) {
        cout << setw(w) << A[i];
    }

    cout << endl;
}

void IO::printArrayDouble(int A[][Globals::MaxGraphSize], const char s[], int w, int count)
{
    cout << endl
         << s;

    cout << "Pointer is : " << A << endl;

    for (int i = 0; i < count; ++i) {
        cout << endl;
        for (int j = 0; j < count; ++j) {
            cout << setw(w) << A[i][j];
        }
    }

    cout << endl;
}

int IO::ReadGraph(int E[][Globals::MaxGraphSize], const char filename[])
{
    std::ifstream myfile(filename);

    if (!myfile.is_open()) {
        return 0;
    }

    int vertexCount;
    myfile >> vertexCount;

    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            int w;
            myfile >> w;
            E[i][j] = w;
        }
    }

    myfile.close();

    return vertexCount;
}