#include <algorithm>
#include <set>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;
class lc242 {
public:
    bool isAnagram(string s, string t) {
        int record[26] = {0};
        for (auto &word : s) { ++record[word - 'a']; }
        for (auto &word : t) { --record[word - 'a']; }
        for (int i : record) {
            if (i != 0) return false;
        }
        return true;
    }
};
class lc349 {
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        unordered_set<int> res;
        unordered_set<int> nums_set(nums1.begin(), nums1.end());
        for (int i : nums2) {
            if (nums_set.find(i) != res.end()) { res.emplace(i); }
        }
        return vector<int>(res.begin(), res.end());
    }
};
class lc202 {
public:
    int getSum(int n) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> sumSet;
        int sum = 0;
        while (1) {
            if (sum == 1) { return true; }
            sum = getSum(n);
            n = sum;
            if (sumSet.find(sum) != sumSet.end()) return false;
            sumSet.emplace(sum);
        }
    }
};
class lc1 {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        std::unordered_map<int, int> num_map{}; // <nums,the index of nums>
        for (int i = 0; i < int(nums.size()); i++) {
            auto first = num_map.find(target - nums[i]);
            if (first != num_map.end()) { return vector<int>{first->second, i}; }
            num_map.emplace(nums[i], i);
        }
        return {};
    }
};
class lc454 {
public:
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                     vector<int> &nums4) {
        unordered_map<int, int> sum12;
        int count = 0;
        for (int i : nums1) {
            for (int j : nums2) { ++sum12[i + j]; }
        }
        for (int k : nums3) {
            for (int l : nums4) {
                auto it = sum12.find(-k - l);
                if (it != sum12.end()) { count += it->second; };
            }
        }
        return count;
    }
};
class lc383 {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<int, int> magazineDeal; // key:word value:number of word
        for (int i : magazine) { ++magazineDeal[i]; }
        for (int j : ransomNote) { --magazineDeal[j]; }
        for (auto k : magazineDeal) {
            if (k.second < 0) { return false; }
        }
        return true;
    }
    // 消耗更小的做法使用数组
    bool canConstruct2(string ransomNote, string magazine) {
        int record[26] = {0};
        // add
        if (ransomNote.size() > magazine.size()) { return false; }
        for (int i = 0; i < magazine.length(); i++) {
            // 通过record数据记录 magazine里各个字符出现次数
            record[magazine[i] - 'a']++;
        }
        for (int j = 0; j < ransomNote.length(); j++) {
            // 遍历ransomNote，在record里对应的字符个数做--操作
            record[ransomNote[j] - 'a']--;
            // 如果小于零说明ransomNote里出现的字符，magazine没有
            if (record[ransomNote[j] - 'a'] < 0) { return false; }
        }
        return true;
    }
};
class lc15 {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> result;
        set<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            int left = i + 1;
            int right = nums.size() - 1;
            if (i > 0 && nums[i] == nums[i - 1]) { continue; }
            while (left < right) {
                if ((nums[i] + nums[left] + nums[right]) > 0) { --right; }
                else if ((nums[i] + nums[left] + nums[right]) < 0) { ++left; }
                else {
                    // result.emplace_back(vector<int>{nums[i], nums[left], nums[right]});
                    res.insert(vector<int>{nums[i], nums[left], nums[right]});
                    --right;
                    ++left;
                }
            }
        }
        return vector<vector<int>>(res.begin(), res.end());
    }
};

int main() {
    vector<int> a{1, 2, 3, -1, -2, -3, -4, 3, 2};
    vector<vector<int>> thr = lc15().threeSum(a);
    int a2;
}