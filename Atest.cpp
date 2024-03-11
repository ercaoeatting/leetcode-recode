#include <vector>

using namespace std;
class Solution {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;
    void backtracking(vector<int>& nums, vector<bool>& used) {
        if (nums.size() == path.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) { continue; }
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};