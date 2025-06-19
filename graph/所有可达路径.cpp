#include <iostream>
#include <list>
#include <vector>

using namespace std;
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path{1};        // 0节点到终点的路径
// x：目前遍历的节点
// graph：存当前的图
// n：终点
//  DFS邻接矩阵
void dfs(vector<vector<int>> &graph, int x, int n) {
    if (x == n) {
        result.push_back(path);
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (graph[x][i]) {
            path.push_back(i);
            dfs(graph, i, n);
            path.pop_back();
        }
    }
}
int 邻接矩阵() {
    int n, m, s, t;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
    while (m--) {
        cin >> s >> t;
        graph[s][t] = 1;
    }
    dfs(graph, 1, n);
    if (result.empty()) cout << -1;
    for (const auto &path : result) {
        for (int i = 0; i < path.size() - 1; i++) {
            cout << path[i] << " ";
        }
        cout << path[path.size() - 1];
        cout << endl;
    }
    return 0;
}
void dfs2(vector<list<int>> &graph, int x, int n) {
    if (x == n) {
        result.push_back(path);
        return;
    }
    for (int i : graph[x]) {
        path.push_back(i);
        dfs2(graph, i, n);
        path.pop_back();
    }
}
int main() {
    int n, m, s, t;
    cin >> n >> m;
    vector<list<int>> graph(n + 1, list<int>{});
    int i = 0;
    while (m--) {
        cin >> s >> t;
        graph[s].push_back(t);
    }
    dfs2(graph, 1, n);
    if (result.empty()) cout << -1;
    for (const auto &path : result) {
        for (int i = 0; i < path.size() - 1; i++) {
            cout << path[i] << " ";
        }
        cout << path[path.size() - 1];
        cout << endl;
    }
    return 0;
}