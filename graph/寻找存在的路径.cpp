#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> father;

public:
    UnionFind(int n) {
        father = vector<int>(n + 1, 0);
        // ranges::iota(father, 0);
        std::iota(father.begin(), father.end(), 0);
    }
    int find(int u) { return u == father[u] ? u : father[u] = find(father[u]); }
    bool is_same(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
    void join(int u, int v) { // u -> v
        u = find(u);
        v = find(v);
        if (u == v) return;
        father[u] = v;
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m;
    UnionFind uf(n);
    while (m--) {
        cin >> s >> t;
        uf.join(s, t);
    }
    int src, des;
    cin >> src >> des;
    cout << (uf.is_same(src, des) ? 1 : 0) << endl;
    return 0;
}