#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

struct Point {
    int x, y;
};

struct Wormhole {
    Point entry, exit;
    int cost;
};

// Function to calculate Manhattan distance
int manhattanDistance(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Find minimum cost to reach destination
int findMinCost(Point source, Point destination, Wormhole wormholes[], int n) {
    const int MAX_NODES = 2 * n + 2;
    const int INF = INT_MAX;
    
    // Graph adjacency matrix (distance between each node)
    int graph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < MAX_NODES; ++i) {
        for (int j = 0; j < MAX_NODES; ++j) {
            graph[i][j] = INF;
        }
    }

    int sourceIdx = 2 * n;  // Index for source
    int destIdx = 2 * n + 1;  // Index for destination

    // Connect source and destination with wormholes
    for (int i = 0; i < n; ++i) {
        int entryIdx = 2 * i;
        int exitIdx = 2 * i + 1;

        // Connect wormhole entry and exit with wormhole cost (bi-directional)
        graph[entryIdx][exitIdx] = wormholes[i].cost;
        graph[exitIdx][entryIdx] = wormholes[i].cost;

        // Connect source to wormhole entry and exit with Manhattan distance
        graph[sourceIdx][entryIdx] = manhattanDistance(source, wormholes[i].entry);
        graph[sourceIdx][exitIdx] = manhattanDistance(source, wormholes[i].exit);

        // Connect destination to wormhole entry and exit with Manhattan distance
        graph[entryIdx][destIdx] = manhattanDistance(destination, wormholes[i].entry);
        graph[exitIdx][destIdx] = manhattanDistance(destination, wormholes[i].exit);

        // Connect wormhole entry/exit pairs with other wormholes using Manhattan distance
        for (int j = i + 1; j < n; ++j) {
            int otherEntryIdx = 2 * j;
            int otherExitIdx = 2 * j + 1;

            graph[entryIdx][otherEntryIdx] = manhattanDistance(wormholes[i].entry, wormholes[j].entry);
            graph[entryIdx][otherExitIdx] = manhattanDistance(wormholes[i].entry, wormholes[j].exit);
            graph[exitIdx][otherEntryIdx] = manhattanDistance(wormholes[i].exit, wormholes[j].entry);
            graph[exitIdx][otherExitIdx] = manhattanDistance(wormholes[i].exit, wormholes[j].exit);
        }
    }

    // Connect source directly to destination
    graph[sourceIdx][destIdx] = manhattanDistance(source, destination);

    // Dijkstra's algorithm without priority queue
    int dist[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 0; i < MAX_NODES; ++i) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[sourceIdx] = 0;

    for (int i = 0; i < MAX_NODES - 1; ++i) {
        // Find the unvisited node with the minimum distance
        int u = -1;
        int minDist = INF;
        for (int j = 0; j < MAX_NODES; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;  // All reachable nodes have been visited
        visited[u] = true;

        // Update distances for all adjacent nodes
        for (int v = 0; v < MAX_NODES; ++v) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    return dist[destIdx];
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        Point source, destination;
        cin >> source.x >> source.y >> destination.x >> destination.y;

        Wormhole wormholes[5];
        for (int i = 0; i < n; ++i) {
            cin >> wormholes[i].entry.x >> wormholes[i].entry.y
                >> wormholes[i].exit.x >> wormholes[i].exit.y >> wormholes[i].cost;
        }

        cout << findMinCost(source, destination, wormholes, n) << endl;
    }

    return 0;
}
