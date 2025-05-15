#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int tspDP(const vector<vector<int>>& dist, int n) {
    int VISITED_ALL = (1 << n) - 1;
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    dp[1][0] = 0; // Start at city 0

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (mask & (1 << u)) {
                for (int v = 0; v < n; ++v) {
                    if ((mask & (1 << v)) == 0) {
                        int nextMask = mask | (1 << v);
                        dp[nextMask][v] = min(dp[nextMask][v], dp[mask][u] + dist[u][v]);
                    }
                }
            }
        }
    }

    int res = INT_MAX;
    for (int i = 1; i < n; ++i) {
        res = min(res, dp[VISITED_ALL][i] + dist[i][0]);
    }
    return res;
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

    cout << "TSP (DP) Result: " << tspDP(dist, n) << endl;
    return 0;
}
