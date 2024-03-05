#include <algorithm>
#include <vector>
#include <string>
using namespace std;
// 组合问题
class lc77 {
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
// 组合总和III
class lc216 {
    vector<vector<int>> result;
    vector<int> path;

public:
    void backtracking(int n, int k, int startindex, int sum) {
        if (path.size() == k) {
            if (sum == n) result.push_back(path);
            return;
        }
        for (int i = startindex; i <= 9; i++) {
            path.push_back(i);
            backtracking(n, k, i + 1, sum + i);
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        int startindex = 0;
        backtracking(n, k, 1, 0);
        return result;
    }
};
// 电话号码组合
class lc17 {
public:
    const string lettermap[10] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz",
    };
    vector<string> result;
    string s;
    void backtracking(string digits, int index) {
        if (index == digits.size()) {
            result.push_back(s);
            return;
        }
        string letter = lettermap[digits[index] - '0'];
        for (int i = 0; i < letter.size(); i++) {
            s.push_back(letter[i]);
            backtracking(digits, index + 1);
            s.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) { return result; }
        backtracking(digits, 0);
        return result;
    }
};
// 组合总和
class lc39 {
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& candidates, int target, int sum, int startindex) {
        if (sum > target) { return; }
        else if (sum == target) {
            result.push_back(path);
            return;
        }
        // for (int i = startindex; i < candidates.size(); i++) {
        // 剪枝
        for (int i = startindex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            path.push_back(candidates[i]);
            backtracking(candidates, target, sum + candidates[i], i);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if (candidates.size() == 0) return result;
        backtracking(candidates, target, 0, 0);
        return result;
    }
};
// 组合总和
class lc40 {
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& candidates, int target, int sum, int startindex,
                      vector<bool> used) {
        if (sum > target) { return; }
        else if (sum == target) {
            result.push_back(path);
            return;
        }
        // for (int i = startindex; i < candidates.size(); i++) {
        // 剪枝
        for (int i = startindex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            // 此处直接通过startindex也可以直接去重，i>startindex && can......就行
            if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false) continue;
            path.push_back(candidates[i]);
            used[i] = true;
            backtracking(candidates, target, sum + candidates[i], i + 1, used);
            used[i] = false;
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        if (candidates.size() == 0) return result;
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0, vector<bool>(candidates.size(), false));
        return result;
    }
};