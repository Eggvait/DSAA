#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int MAX = 20;
int graph[MAX][MAX];  // adjacency matrix
int V;                // number of vertices

// For Kruskal's
struct Edge {
    int src, dest, weight;
};

bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Union-Find for Kruskal's
int parent[MAX];

int find(int i) {
    if (parent[i] == -1) return i;
    return parent[i] = find(parent[i]);
}

void unionSet(int x, int y) {
    int xset = find(x);
    int yset = find(y);
    if (xset != yset) parent[xset] = yset;
}

// Prim's Algorithm
void prims() {
    int key[MAX], parent[MAX];
    bool mstSet[MAX];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, u;
        for (int v = 0; v < V; v++)
            if (!mstSet[v] && key[v] < min)
                min = key[v], u = v;

        mstSet[u] = true;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    cout << "Prim's MST:\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
}

// Kruskal's Algorithm
void kruskal() {
    vector<Edge> edges;

    // Create edge list
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j])
                edges.push_back({i, j, graph[i][j]});
        }
    }

    sort(edges.begin(), edges.end(), compareEdge);

    for (int i = 0; i < V; i++)
        parent[i] = -1;

    cout << "Kruskal's MST:\n";
    int count = 0;
    for (auto edge : edges) {
        int u = find(edge.src);
        int v = find(edge.dest);

        if (u != v) {
            cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
            unionSet(u, v);
            count++;
        }

        if (count == V - 1) break;
    }
}

// Dijkstra's Algorithm
void dijkstra(int src) {
    int dist[MAX];
    bool visited[MAX] = {false};

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, u;

        for (int i = 0; i < V; i++)
            if (!visited[i] && dist[i] <= min)
                min = dist[i], u = i;

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    cout << "Dijkstra's Shortest Paths from node " << src << ":\n";
    for (int i = 0; i < V; i++)
        cout << "To " << i << " : " << dist[i] << endl;
}

// Input Graph
void inputGraph() {
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter adjacency matrix (0 if no edge):\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];
}

// Main Menu
int main() {
    int choice;
    while (true) {
        cout << "\n--- Graph Algorithms Menu ---\n";
        cout << "1. Input Graph\n";
        cout << "2. Prim's Algorithm (MST)\n";
        cout << "3. Kruskal's Algorithm (MST)\n";
        cout << "4. Dijkstra's Algorithm (SSSP)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputGraph();
                break;
            case 2:
                if (V > 0) prims();
                else cout << "Input the graph first.\n";
                break;
            case 3:
                if (V > 0) kruskal();
                else cout << "Input the graph first.\n";
                break;
            case 4:
                if (V > 0) {
                    int src;
                    cout << "Enter source vertex: ";
                    cin >> src;
                    if (src >= 0 && src < V)
                        dijkstra(src);
                    else
                        cout << "Invalid source vertex!\n";
                } else {
                    cout << "Input the graph first.\n";
                }
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
