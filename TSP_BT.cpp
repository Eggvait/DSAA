#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int tspBT(const vector<vector<int>>& dist, int n) {
    vector<int> cities;
    for (int i = 1; i < n; ++i) cities.push_back(i);
    int minPath = INT_MAX;

    do {
        int currPath = dist[0][cities[0]];
        for (int i = 0; i < cities.size() - 1; ++i)
            currPath += dist[cities[i]][cities[i + 1]];
        currPath += dist[cities.back()][0];
        minPath = min(minPath, currPath);
    } while (next_permutation(cities.begin(), cities.end()));

    return minPath;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter distance matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> dist[i][j];

    cout << "TSP (Backtracking) Result: " << tspBT(dist, n) << endl;
    return 0;
}
