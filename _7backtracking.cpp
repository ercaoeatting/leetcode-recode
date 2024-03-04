#include <vector>

using namespace std;
// 组合问题
class Solution {
    vector<vector<int>> result;
    vector<int> path;

public:
    void backtracking(int n, int k, int startindex) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = startindex; i <= n; i++) {
            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        int startindex = 0;
        backtracking(n, k, 1);
        return result;
    }
};