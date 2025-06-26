
#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
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
bool is_tree_after_del(vector<vector<int>> &paths, int index) {
    unionFind uf(paths.size());
    for (int i = 0; i < paths.size(); i++) {
        if (i == index) continue;
        if (uf.is_same(paths[i]))
            return false;
        else {
            uf.join(paths[i]);
        }
    }
    return true;
}
void is_tree(vector<vector<int>> &paths) {
    unionFind uf(paths.size());
    for (auto &x : paths) {
        if (uf.is_same(x)) {
            cout << x[0] << " " << x[1] << endl;
            return;
        } else {
            uf.join(x);
        }
    }
}
int main() {
    int n;
    cin >> n;
    int s, t;
    vector<vector<int>> paths;
    vector<int> inDegree(n + 1, 0);
    while (n--) {
        cin >> s >> t;
        inDegree[t]++;
        paths.push_back({s, t});
    }
    vector<int> vec;
    for (int i = n - 1; i >= 0; i--) {
        if (inDegree[paths[i][1]] == 2) vec.push_back(i);
    }
    if (!vec.empty()) {
        if (is_tree_after_del(paths, vec[0])) {
            cout << paths[vec[0]][0] << " " << paths[vec[0]][1] << endl;
        } else {
            cout << paths[vec[1]][0] << " " << paths[vec[1]][1] << endl;
        }
    } else {
        is_tree(paths);
    }
}