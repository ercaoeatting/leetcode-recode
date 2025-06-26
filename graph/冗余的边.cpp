
#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
class unionFind {
    vector<int> father;
    size_t size_;

public:
    unionFind(int n) {
        father = vector<int>(n + 1, 0);
        size_ = n;
        std::iota(father.begin(), father.end(), 0);
    }
    int find(int u) { return u == father[u] ? u : father[u] = find(father[u]); }
    bool is_same(int u, int v) {
        u = find(u);
        v = find(v);
        return u == v;
    }
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        father[u] = v;
    }
    int size() { return size_; }
};

int main() {
    int n;
    cin >> n;
    unionFind uf(n);
    int a, b;
    while (n--) {
        cin >> a >> b;
        if (!uf.is_same(a, b))
            uf.join(a, b);
        else {
            cout << a << " " << b << endl;
            return 0;
        }
    }
}