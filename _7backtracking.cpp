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
            sum += i;
            backtracking(n, k, i + 1, sum);
            path.pop_back();
            sum -= i;
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        int startindex = 0;
        backtracking(n, k, 1, 0);
        return result;
    }
};

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