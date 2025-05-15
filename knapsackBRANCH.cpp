#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight, value;
    double ratio;
};

bool cmp(Item a, Item b) {
    return a.ratio > b.ratio;
}

struct Node {
    int level, profit, weight;
    double bound;
};

// Estimate upper bound on max profit for a node
double bound(Node u, int n, int W, vector<Item>& items) {
    if (u.weight >= W) return 0;

    double profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;

    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    if (j < n)
        profitBound += (W - totalWeight) * items[j].ratio;

    return profitBound;
}

// Main Branch and Bound function
int knapsackBB(int W, vector<Item> items) {
    sort(items.begin(), items.end(), cmp);

    queue<Node> Q;
    Node u, v;

    v.level = -1; v.profit = 0; v.weight = 0;
    v.bound = bound(v, items.size(), W, items);
    Q.push(v);

    int maxProfit = 0;

    while (!Q.empty()) {
        v = Q.front(); Q.pop();
        if (v.level == (int)items.size() - 1) continue;

        u.level = v.level + 1;
        u.weight = v.weight + items[u.level].weight;
        u.profit = v.profit + items[u.level].value;

        if (u.weight <= W && u.profit > maxProfit)
            maxProfit = u.profit;

        u.bound = bound(u, items.size(), W, items);
        if (u.bound > maxProfit) Q.push(u);

        u.weight = v.weight;
        u.profit = v.profit;
        u.bound = bound(u, items.size(), W, items);
        if (u.bound > maxProfit) Q.push(u);
    }

    return maxProfit;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    vector<Item> items(n);

    cout << "Enter weights of items: ";
    for(int i = 0; i < n; ++i) cin >> items[i].weight;

    cout << "Enter values of items: ";
    for(int i = 0; i < n; ++i) cin >> items[i].value;

    for(int i = 0; i < n; ++i)
        items[i].ratio = (double)items[i].value / items[i].weight;

    cout << "Enter knapsack capacity: ";
    cin >> W;

    cout << "Branch and Bound Result: " << knapsackBB(W, items) << endl;
    return 0;
}
