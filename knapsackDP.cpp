#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to solve knapsack using DP
int knapsackDP(int W, vector<int> wt, vector<int> val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));  // DP table

    for(int i = 1; i <= n; ++i) {
        for(int w = 0; w <= W; ++w) {
            if(wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];  // max value that can be achieved
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> wt(n), val(n);
    cout << "Enter weights of items: ";
    for(int i = 0; i < n; ++i) cin >> wt[i];

    cout << "Enter values of items: ";
    for(int i = 0; i < n; ++i) cin >> val[i];

    cout << "Enter knapsack capacity: ";
    cin >> W;

    cout << "DP Result: " << knapsackDP(W, wt, val, n) << endl;
    return 0;
}
