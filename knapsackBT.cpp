#include <iostream>
#include <vector>
using namespace std;

int maxVal = 0;  // global maximum

// Recursive function for 0/1 knapsack using backtracking
void knapsackBT(int i, int n, int W, int currWeight, int currValue, vector<int>& wt, vector<int>& val) {
    if (i == n) {
        maxVal = max(maxVal, currValue);
        return;
    }

    if (currWeight + wt[i] <= W)
        knapsackBT(i + 1, n, W, currWeight + wt[i], currValue + val[i], wt, val);

    knapsackBT(i + 1, n, W, currWeight, currValue, wt, val);
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

    knapsackBT(0, n, W, 0, 0, wt, val);
    cout << "Backtracking Result: " << maxVal << endl;
    return 0;
}
