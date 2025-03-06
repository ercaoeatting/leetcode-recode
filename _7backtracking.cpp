#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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
// 分割问题
class lc131 {
    vector<vector<string>> result;
    vector<string> str;

public:
    bool ifretstr(string s) {
        int left = 0, right = s.size() - 1;
        while (left <= right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }
    void backtracking(string s) {
        if (1 > s.size()) {
            result.push_back(str);
            return;
        }
        for (int i = 1; i <= s.size(); i++) {
            string subs = string(s.begin(), s.begin() + i);
            if (ifretstr(subs)) {
                str.push_back(subs);
                backtracking(string(s.begin() + i, s.end()));
                str.pop_back();
            }
            else { continue; }
        }
    }
    vector<vector<string>> partition(string s) {
        if (s.size() == 0) return result;
        backtracking(s);
        return result;
    }
};
class lc131_sol2 {
private:
    vector<vector<string>> result;
    vector<string> path;               // 放已经回文的子串
    vector<vector<bool>> isPalindrome; // 放事先计算好的是否回文子串的结果
    void backtracking(const string& s, int startIndex) {
        // 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
        if (startIndex >= s.size()) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isPalindrome[startIndex][i]) { // 是回文子串
                // 获取[startIndex,i]在s中的子串
                string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
            }
            else { // 不是回文，跳过
                continue;
            }
            backtracking(s, i + 1); // 寻找i+1为起始位置的子串
            path.pop_back();        // 回溯过程，弹出本次已经添加的子串
        }
    }
    void computePalindrome(const string& s) {
        // isPalindrome[i][j] 代表 s[i:j](双边包括)是否是回文字串
        isPalindrome.resize(s.size(),
                            vector<bool>(s.size(), false)); // 根据字符串s, 刷新布尔矩阵的大小
        for (int i = s.size() - 1; i >= 0; i--) {
            // 需要倒序计算, 保证在i行时, i+1行已经计算好了
            for (int j = i; j < s.size(); j++) {
                if (j == i) { isPalindrome[i][j] = true; }
                else if (j - i == 1) { isPalindrome[i][j] = (s[i] == s[j]); }
                else { isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i + 1][j - 1]); }
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        result.clear();
        path.clear();
        computePalindrome(s);
        backtracking(s, 0);
        return result;
    }
};

// 复原IP地址
class lc93 {
    vector<string> result;
    bool isValid(const string& s, int start, int end) {
        if (start > end) { return false; }
        if (s[start] == '0' && start != end) { // 0开头的数字不合法
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }
    void backtracking(string& s, int startIndex, int point) {
        if (point == 3) {
            if (isValid(s, startIndex, s.size() - 1)) {
                result.push_back(s);
                return;
            }
        }
        for (int i = startIndex; i < s.size(); i++) {
            if (isValid(s, startIndex, i)) {
                s.insert(s.begin() + i + 1, '.');
                backtracking(s, i + 2, point + 1);
                s.erase(s.begin() + i + 1);
            }
            else
                break;
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        if (s.size() < 4 || s.size() > 12) return result;
        backtracking(s, 0, 0);
        return result;
    }
};
// 子集问题
class lc78 {
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& nums, int start) {
        result.push_back(path);
        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};

class lc90 {
    vector<int> path;
    vector<vector<int>> result;

public:
    void backtracking(vector<int>& nums, int start) {
        result.push_back(path);
        if (start >= nums.size()) return;
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i - 1]) continue;
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return result;
    }
};

// 非递减子序列
class lc491 {
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int start) {
        if (path.size() > 1) result.push_back(path);
        if (start >= nums.size()) return;

        unordered_set<int> uset;
        for (int i = start; i < nums.size(); i++) {
            if ((!path.empty() && nums[i] < path.back()) || uset.find(nums[i]) != uset.end())
                continue;
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};
// 排列问题
// 全排列
class lc46 {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;
    void backtracking(vector<int>& nums, vector<bool>& used) {
        int use = 1;
        for (int i = 0; i < used.size(); i++) {
            if (used[i] == 0) use = 0;
        }
        if (use) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
class lc47 {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, vector<bool>& used) {
        // 此时说明找到了一组
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            // used[i - 1] == true，说明同一树枝nums[i - 1]使用过
            // used[i - 1] == false，说明同一树层nums[i - 1]使用过
            // 如果同一树层nums[i - 1]使用过则直接跳过
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) { continue; }
            if (used[i] == false) {
                used[i] = true;
                path.push_back(nums[i]);
                backtracking(nums, used);
                path.pop_back();
                used[i] = false;
            }
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end()); // 排序
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};

// 重新规划行程
class lc332 {
public:
    unordered_map<string, map<string, int>> targets;
    vector<string> result;
    bool backtracking(int ticketnum) {
        if (result.size() == ticketnum + 1) { return true; }
        for (auto& target : targets[result[result.size() - 1]]) {
            if (target.second > 0) {
                result.push_back(target.first);
                target.second--;
                if (backtracking(ticketnum)) return true;
                target.second++;
                result.pop_back();
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (const vector<string>& vec : tickets) {
            targets[vec[0]][vec[1]]++; // 记录映射关系
        }
        result.push_back("JFK"); // 起始机场
        backtracking(tickets.size());
        return result;
    }
};
// 棋盘问题
// N皇后
class lc51 {
    vector<vector<string>> result;
    bool isValid(int row, int col, vector<string>& chessboard, int n) {
        // 检查列
        for (int i = 0; i < row; i++) {
            if (chessboard[i][col] == 'Q') return false;
        }
        // 斜线
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (chessboard[i][j] == 'Q') return false;
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j <= n; i--, j++) {
            if (chessboard[i][j] == 'Q') return false;
        }
        return true;
    }
    void backtracking(int n, int row, vector<string>& chessboard) {
        if (row == n) {
            result.push_back(chessboard);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(row, col, chessboard, n)) {
                chessboard[row][col] = 'Q';
                backtracking(n, row + 1, chessboard);
                chessboard[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessboard(n, string(n, '.'));
        backtracking(n, 0, chessboard);
        return result;
    }
};
// 解数独
class lc37 {
public:
    bool isValid(int i, int j, char k, const vector<vector<char>>& board) {
        // 检查行
        for (int row = 0; row < 9; row++) {
            if (board[row][j] == k) return false;
        }
        // 检查列
        for (int line = 0; line < 9; line++) {
            if (board[i][line] == k) return false;
        }
        // 检查本宫格
        int startrow = (i / 3) * 3;
        int startcol = (j / 3) * 3;
        for (int row = startrow; row < startrow + 3; row++) {
            for (int col = startcol; col < startcol + 3; col++) {
                if (board[row][col] == k) return false;
            }
        }
        return true;
    }
    bool backtracking(vector<vector<char>>& board, int row, int line) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') continue;
                for (char k = '1'; k <= '9'; k++) {
                    if (isValid(i, j, k, board)) {
                        board[i][j] = k;
                        if (backtracking(board, i + 1, j + 1)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) { backtracking(board, 0, 0); }
};
int main() {}