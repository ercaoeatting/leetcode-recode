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
    queue<string> que;
    unordered_map<string, int> strpath;
    strpath.insert({beginStr, 1});
    que.push(beginStr);
    while (!que.empty()) {
        string word = que.front();
        que.pop();
        for (int i = 0; i < word.size(); i++) {
            string newword = word;
            int path = strpath[word];
            for (char c = 'a'; c <= 'z'; c++) {
                newword[i] = c;
                if (newword == endStr) {
                    cout << path + 1 << endl;
                    return 0;
                }
                if (strSet.count(newword) && !strpath.count(newword)) {
                    strpath.insert({newword, path + 1});
                    que.push(newword);
                }
            }
        }
    }
    cout << 0 << endl;
}