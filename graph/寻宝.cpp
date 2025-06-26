#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>

using namespace std;

int prim() {
    int v, e;
    cin >> v >> e;
    vector<vector<int>> grid(v, vector<int>(v, INT_MAX));
    int v1, v2, val;
    while (e--) {
        cin >> v1 >> v2 >> val;
        grid[v1 - 1][v2 - 1] = val; // 编号 1-v -> 0 - v-1
        grid[v2 - 1][v1 - 1] = val;
    }
    vector<int> isintree(v, 0);
    vector<int> mindist(v, INT_MAX);
    mindist[0] = 0;
    int count = 0;
    for (int i = 0; i < v; i++) {
        int cur = -1;
        int minval = INT_MAX;
        for (int j = 0; j < v; j++) {
            if (!isintree[j] && mindist[j] < minval) {
                minval = mindist[j];
                cur = j;
            }
        }
        count += minval;

        isintree[cur] = 1;

        for (int j = 0; j < v; j++) {
            if (!isintree[j] && grid[cur][j] < mindist[j]) {
                mindist[j] = grid[cur][j];
            }
        }
    }
    cout << count << endl;
    return 0;
}

struct Edge {
    int i;
    int j;
    int dis;
    std::strong_ordering operator<=>(const Edge &other) const = default;
};
ostream &operator<<(ostream &os, const Edge &it) {
    os << it.i << " " << it.j << ":" << it.dis;
    return os;
}
class unionFind {
    vector<int> father;
    vector<int> father_init;

public:
    unionFind(int n) {
        father = vector<int>(n + 1, 0);
        std::iota(father.begin(), father.end(), 0);
        father_init = father;
    }
    void init() { father = father_init; }
    int find(int u) { return u == father[u] ? u : father[u] = find(father[u]); }
    bool is_same(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
    bool is_same(vector<int> &uv) { return is_same(uv[0], uv[1]); }
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        father[u] = v;
    }
    void join(vector<int> &uv) { join(uv[0], uv[1]); }
};
int main() {
    int v, e; // v 点数  e 边数
    cin >> v >> e;
    vector<vector<int>> grid(v, vector<int>(v, INT_MAX));
    vector<Edge> edges;
    int v1, v2, val;
    unionFind uf(e);
    while (e--) {
        cin >> v1 >> v2 >> val;
        grid[v1 - 1][v2 - 1] = val; // 编号 1-v -> 0 - v-1
        grid[v2 - 1][v1 - 1] = val;
        edges.push_back({v1, v2, val});
    }
    int count = 0;
    sort(edges.begin(), edges.end(), [](Edge left, Edge right) { return left.dis < right.dis; });
    vector<Edge> res;
    for (int i = 0; i < edges.size(); i++) {
        if (!uf.is_same(edges[i].i, edges[i].j)) {
            count += edges[i].dis;
            uf.join(edges[i].i, edges[i].j);
            // cout << edges[i] << endl;
            res.push_back(edges[i]);
        }
    }
    cout << count << endl;
}