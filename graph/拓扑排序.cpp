#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n, m, s, t;
    cin >> n >> m;
    unordered_map<int, vector<int>> rely;
    vector<int> indeg(n, 0);
    while (m--) {
        cin >> s >> t; // t relay on s
        rely[s].push_back(t);
        indeg[t]++;
    }
    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            que.push(i);
        }
    }

    vector<int> res;
    while (!que.empty()) {
        int index = que.front();
        que.pop();
        res.push_back(index);
        vector<int> files = rely[index];
        if (!files.empty()) {
            for (int file : files) {
                if (--indeg[file] == 0) que.push(file);
            }
        }
    }
    if (res.size() == n) {
        for (int i = 0; i < n - 1; i++) {
            cout << res[i] << " ";
        }
        cout << res[n - 1];
    } else {
        cout << -1 << endl;
    }
}