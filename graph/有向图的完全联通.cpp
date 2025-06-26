#include <iostream>
#include <list>
#include <vector>
using namespace std;

void dfs(vector<list<int>> &g, vector<int> &visited, int x, int n) {
    if (x == n) {
        visited[n] = 0;
        return;
    }
    for (int gx : g[x]) {
        visited[gx] = 1;
        dfs(g, visited, gx, n);
    }
}

int main() {
    int n, k, s, t;
    cin >> n >> k;
    vector<list<int>> graph(n + 1, list<int>{});
    while (k--) {
        cin >> s >> t;
        graph[s].push_back(t);
    }
    vector<int> visited(n + 1, 0);
    dfs(graph, visited, 1, n);
    for (int x : visited) {
        if (x == 0) {
            cout << -1 << endl;
            return 0;
        }
    }
    cout << 1 << endl;
    return 0;
}