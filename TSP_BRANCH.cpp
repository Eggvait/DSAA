#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int tspBBUtil(const vector<vector<int>>& dist, vector<bool>& visited, int currPos, int count, int cost, int& ans, int n) {
    if (count == n && dist[currPos][0]) {
        ans = min(ans, cost + dist[currPos][0]);
        return ans;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dist[currPos][i]) {
            visited[i] = true;
            tspBBUtil(dist, visited, i, count + 1, cost + dist[currPos][i], ans, n);
            visited[i] = false;
        }
    }
    return ans;
}

int tspBB(const vector<vector<int>>& dist, int n) {
    vector<bool> visited(n, false);
    visited[0] = true;
    int ans = INT_MAX;
    return tspBBUtil(dist, visited, 0, 1, 0, ans, n);
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

    cout << "TSP (Branch and Bound) Result: " << tspBB(dist, n) << endl;
    return 0;
}
