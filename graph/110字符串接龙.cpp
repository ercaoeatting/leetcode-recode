#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {
    string beginStr, endStr, str;
    int n;
    cin >> n;
    unordered_set<string> strSet;
    cin >> beginStr >> endStr;
    for (int i = 0; i < n; i++) {
        cin >> str;
        strSet.insert(str);
    }
    unordered_map<string, int> visited_map;
    visited_map[beginStr] = 1;
    queue<string> que;
    que.push(beginStr);
    while (!que.empty()) {
        string word = que.front();
        que.pop();
        int path = visited_map[word];
        for (int i = 0; i < word.size(); i++) {
            string new_wd = word;
            for (char c = 'a'; c <= 'z'; c++) {
                new_wd[i] = c;
                if (new_wd == endStr) {
                    cout << path + 1 << endl;
                    return 0;
                }
                if (!visited_map.count(new_wd) && strSet.count(new_wd)) {
                    que.push(new_wd);
                    visited_map[new_wd] = path + 1;
                }
            }
        }
    }
    cout << 0 << endl;
    return 0;
}