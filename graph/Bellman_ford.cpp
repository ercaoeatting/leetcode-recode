#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g;
    int size = n;
    while (m--) {
        int s, t, val;
        cin >> s >> t >> val;
        g.push_back({s, t, val});
    }
    vector<int> mindist(n + 1, INT_MAX);
    mindist[1] = 0;
    while (size--) {
        for (auto &s : g) {
            int from = s[0], to = s[1], price = s[2];
            if (mindist[from] != INT_MAX && mindist[from] + price < mindist[to]) {
                mindist[to] = mindist[from] + price;
            }
        }
    }
    cout << ((mindist[n] == INT_MAX) ? "unconnected" : to_string(mindist[n])) << endl;
}