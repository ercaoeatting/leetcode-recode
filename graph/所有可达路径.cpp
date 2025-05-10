#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> result; // 收集符合条件的路径
vector<int> path;           // 0节点到终点的路径
// x：目前遍历的节点
// graph：存当前的图
// n：终点
//  DFS邻接矩阵
void dfs(const vector<vector<int>>& graph, int x, int n) {
    if (x == n) {
        result.push_back(path);
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (graph[x][i] == 1) {
            path.push_back(i);
            dfs(graph, i, n);
            path.pop_back();
        }
    }
};
int 邻接矩阵写法() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
    while (m--) {
        int s, t;
        cin >> s >> t;
        // 使用邻接矩阵 ，1 表示 节点s 指向 节点t
        graph[s][t] = 1;
    }
    path.push_back(1);
    dfs(graph, 1, n);
    if (result.size() == 0) cout << -1 << endl;
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size() - 1; j++) {
            cout << result[i][j] << " ";
        }
        cout << result[i][result[i].size() - 1] << endl;
    }
    return 0;
}