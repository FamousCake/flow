#include <iostream>
#include <vector>

#include <utility>

#include <algorithm> // std::shuffle
#include <random>    // std::default_random_engine
#include <chrono>

using namespace std;

void writeGraph(int vCount, long eCount, int min, int max, int source, int sink)
{
    //
    // 1. Declare everything needed
    //
    std::vector<std::vector<bool>> E(vCount, std::vector<bool>(vCount, false));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    //
    // 2. Prepare the list of all possible edges
    //
    vector<pair<int, int>> eList;

    for (int i = 0; i < vCount; ++i)
    {
        for (int j = 0; j < vCount; ++j)
        {
            if (i != j)
            {
                eList.push_back(pair<int, int>(i, j));
            }
        }
    }

    //
    // 3. Shuffle the list
    //
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(eList.begin(), eList.end(), std::default_random_engine(seed));

    //
    // 4. Output edges
    //
    long edgeCount = 0;
    for (auto temp : eList)
    {

        int i = temp.first;
        int j = temp.second;

        if (i == sink || j == source || E[j][i] == true)
        {
            continue;
        }

        E[i][j] = true;
        edgeCount++;

        cout << "a " << i + 1 << " " << j + 1 << " " << dist(mt) << endl;

        if (edgeCount == eCount)
        {
            break;
        }
    }
}

void writeSparseGraph(int vCount, long eCount, int min, int max, int source, int sink)
{
    std::vector<std::vector<bool>> E(vCount, std::vector<bool>(vCount, false));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    std::uniform_int_distribution<int> distI(0, vCount-2);
    std::uniform_int_distribution<int> distJ(1, vCount-1);

    while (eCount > 0) {
        int i = distI(mt);
        int j = distJ(mt);

        if (E[i][j] == true || E[j][i] == true || i == j) {
            continue;
        }

        E[i][j] = true;
        cout << "a " << i + 1 << " " << j + 1 << " " << dist(mt) << endl;
        eCount--;
    }
}

int main(int argc, char *argv[])
{
    long n;
    long edgeCount;// = (density * ((n * n) - n)) / 100;
    string type;
    int min, max;

    type = argv[1];
    n = std::stol(argv[2]);
    edgeCount = std::stol(argv[3]);
    min = std::stoi(argv[4]);
    max = std::stoi(argv[5]);

    cout << "c" << endl;
    cout << "c This is a generated graph" << endl;
    cout << "c" << endl;
    cout << "p max " << n << " " << edgeCount << endl;
    cout << "c" << endl;
    cout << "c" << endl;
    cout << "n " << 1 << " s" << endl;
    cout << "n " << n << " t" << endl;
    cout << "c" << endl;
    cout << "c" << endl;

    if (type.compare("shuffle") == 0) {
        writeGraph(n, edgeCount, min, max, 0, n-1);
    }
    else if (type.compare("random") == 0) {
        writeSparseGraph(n, edgeCount, min, max, 0, n-1);
    }

    return 0;
}
