#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class 所有可能的路径797 {
    vector<int> path{0};
    vector<vector<int>> res;
    void dfs(const vector<vector<int>>& graph, int x, int n) {
        if (x == n) {
            res.push_back(path);
            return;
        }
        for (int i : graph[x]) {
            path.push_back(i);
            dfs(graph, i, n);
            path.pop_back();
        }
        return;
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        dfs(graph, 0, graph.size() - 1);
        return res;
    }
};