#include <climits>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

int 朴素版() {
    int n, m;
    cin >> n >> m;
    int s, e, v;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INT_MAX));
    while (m--) {
        cin >> s >> e >> v;
        graph[s][e] = v; // s -> e
    }
    vector<int> used(n + 1, false);
    vector<int> mindist(n + 1, INT_MAX);
    mindist[1] = 0;
    for (int i = 1; i <= n; i++) {
        int cur = 1;
        int minval = INT_MAX;
        for (int v = 1; v <= n; v++) {
            if (!used[v] && mindist[v] < minval) {
                minval = mindist[v];
                cur = v;
            }
        }
        used[cur] = true;
        for (int v = 1; v <= n; v++) {
            if (!used[v] && graph[cur][v] != INT_MAX && mindist[v] > mindist[cur] + graph[cur][v]) {
                mindist[v] = mindist[cur] + graph[cur][v];
            }
        }
    }
    cout << ((mindist[n] == INT_MAX) ? -1 : mindist[n]) << endl;
    return 0;
}

struct Edge {
    int no;
    int val;
    Edge(int d, int v) :
        no(d), val(v){};
};
int main() {
    int n, m;
    cin >> n >> m;
    int s, e, v;
    vector<list<Edge>> graph(n + 1);
    while (m--) {
        cin >> s >> e >> v;
        graph[s].push_back({e, v});
    }
    vector<bool> used(n + 1, false);
    vector<int> mindist(n + 1, INT_MAX);
    auto compare1 =
        [](const Edge &l, const Edge &r) { return l.val > r.val; };
    priority_queue<Edge, vector<Edge>, decltype(compare1)> pq(compare1);
    pq.push({1, 0});
    mindist[1] = 0;
    while (!pq.empty()) {
        Edge cur = pq.top();
        pq.pop();
        if (used[cur.no]) continue;
        used[cur.no] = true;
        for (auto &to : graph[cur.no]) {
            if (!used[to.no] && mindist[cur.no] + to.val < mindist[to.no]) {
                mindist[to.no] = mindist[cur.no] + to.val;
                pq.push({to.no, mindist[to.no]});
            }
        }
    }
    cout << (mindist[n] == INT_MAX ? -1 : mindist[n]) << endl;
}