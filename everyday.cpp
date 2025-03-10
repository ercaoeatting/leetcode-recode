#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class FindElements {
    unordered_set<int> valSet;

public:
    void build(TreeNode *root, int val) {
        if (!root) return;
        root->val = val;
        valSet.insert(val);
        if (root->left) build(root->left, 2 * root->val + 1);
        if (root->right) build(root->left, 2 * root->val + 2);
    }
    FindElements(TreeNode *root) { build(root, 0); }

    bool find(int target) { return valSet.count(target) == 1; }
};

class FinalString {
public:
    void reverse(string &s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
    string finalString(string s) {
        string res;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'i') { reverse(res); }
            else { res.push_back(s[i]); }
        }
        return res;
    }
};

class MyHashSet {
private:
    vector<list<int>> data;
    static const int base = 769;
    static int hash(int key) { return key % base; }

public:
    MyHashSet() : data(base) {}

    void add(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key) return;
        }
        data[h].push_back(key);
    }

    void remove(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key) {
                data[h].erase(it);
                return;
            }
        }
    }

    bool contains(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key) { return true; }
        }
        return false;
    }
};

// 2502. 设计内存分配器

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */
class MyAllocator {
    vector<int> array_;
    vector<vector<int>> check_;
    int n_;

public:
    MyAllocator(int n) : n_(n), array_(n) {}

    int allocate(int size, int mID) {
        if (size <= 0 || size > n_) return -1;
        vector<vector<int>> can;
        if (check_.empty()) { can.push_back({0, n_ - 1}); }
        else {
            int begin1 = check_[0][0];
            int end1 = check_[0][1];
            if (begin1 > 0) { can.push_back({0, begin1 - 1}); }
            for (int i = 1; i < check_.size(); i++) {
                int begin2 = check_[i][0];
                int end2 = check_[i][1];
                if (begin2 > end1 + 1) can.push_back({end1 + 1, begin2 - 1});
                begin1 = begin2;
                end1 = end2;
            }
            if (end1 < n_ - 1) { can.push_back({end1 + 1, n_ - 1}); }
        }
        for (auto &block : can) {
            int start = block[0];
            int end = block[1];
            int available_size = end - start + 1;
            if (available_size >= size) {
                // 分配内存，并插入到 check_ 的正确位置以保持有序
                vector<int> new_block = {start, start + size - 1, mID};
                auto insert_pos = lower_bound(
                    check_.begin(), check_.end(), new_block,
                    [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
                check_.insert(insert_pos, new_block);

                // 标记内存为 mID
                fill(array_.begin() + start, array_.begin() + start + size, mID);
                return start; // 返回分配的内存起始位置
            }
        }
        return -1;
    }
    int freeMemory(int mID) {
        int count = 0;
        // 遍历 check_，释放所有标记为 mID 的内存块
        for (auto it = check_.begin(); it != check_.end();) {
            if ((*it)[2] == mID) {
                // 标记内存为 0
                for (int i = (*it)[0]; i <= (*it)[1]; i++) { array_[i] = 0; }
                it = check_.erase(it); // 从 check_ 中移除该内存块
                count++;
            }
            else { it++; }
        }
        return count; // 返回释放的内存块数量
    }
};

// 作者：力扣官方题解
class Allocator {
public:
    Allocator(int n) : n(n), memory(n) {}

    int allocate(int size, int mID) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (memory[i]) { count = 0; }
            else {
                ++count;
                if (count == size) {
                    for (int j = i - count + 1; j <= i; ++j) { memory[j] = mID; }
                    return i - count + 1;
                }
            }
        }
        return -1;
    }

    int freeMemory(int mID) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (memory[i] == mID) {
                ++count;
                memory[i] = 0;
            }
        }
        return count;
    }

private:
    int n;
    vector<int> memory;
};

class BrowserHistory {
    stack<string> stack1;
    stack<string> stack2;

public:
    BrowserHistory(string homepage) { stack1.push(homepage); }

    void visit(string url) {
        stack1.push(url);
        while (!stack2.empty()) { stack2.pop(); }
    };

    string back(int steps) {
        while (steps--) {
            if (stack1.size() <= 1) break;
            stack2.push(stack1.top());
            stack1.pop();
        }
        return stack1.top();
    }

    string forward(int steps) {
        while (steps--) {
            if (stack2.empty()) break;
            stack1.push(stack2.top());
            stack2.pop();
        }
        return stack1.top();
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */
class TextEditor {
    vector<char> texts;
    vector<char>::iterator cursor;

public:
    TextEditor() { cursor = texts.end(); }

    void addText(string text) {
        for (char c : text) { texts.insert(cursor, c); }
    }

    int deleteText(int k) {
        int count = 0;
        while (k-- && cursor != texts.begin()) {
            texts.erase(prev(cursor));
            count++;
        }
        return count;
    }

    string cursorLeft(int k) {
        while (cursor != texts.begin() && k--) { cursor = prev(cursor); }
        auto head = cursor;
        for (int i = 0; i < 10 && head != texts.begin(); i++) { head = prev(head); }
        return string(head, cursor);
    }

    string cursorRight(int k) {
        while (cursor != texts.end() && k--) { cursor = next(cursor); }
        auto head = cursor;
        for (int i = 0; i < 10 && head != texts.begin(); i++) { head = prev(head); }
        return string(head, cursor);
    }
};
class MyFoodRatings {
    class FoodRatings {
        unordered_map<string, pair<int, string>> food_map;         // 食物 -> <评分，烹饪方式>
        unordered_map<string, set<pair<int, string>>> cuisine_map; // 烹饪方式 -> <食物评分，食物名>

    public:
        FoodRatings(vector<string> &foods, vector<string> &cuisines, vector<int> &ratings) {
            for (int i = 0; i < foods.size(); i++) {
                food_map[foods[i]] = {ratings[i], cuisines[i]};
                cuisine_map[cuisines[i]].emplace(-ratings[i], foods[i]);
            }
        }

        void changeRating(string food, int newRating) {
            auto &food_info = food_map[food]; // food_info food的评分和烹饪方式
            cuisine_map[food_info.second].erase({-food_info.first, food});
            cuisine_map[food_info.second].emplace(-newRating, food);
            food_map[food].first = newRating;
        }

        string highestRated(string cuisine) { return cuisine_map[cuisine].begin()->second; }
    };

    // leetcode.cn/problems/design-a-food-rating-system/solutions/1694044/ha-xi-biao-tao-ping-heng-shu-by-endlessc-hzct/
public:
    unordered_map<string, vector<pair<string, int>>> foodmap;
    MyFoodRatings(vector<string> &foods, vector<string> &cuisines, vector<int> &ratings) {
        for (int i = 0; i < cuisines.size(); i++) {
            foodmap[cuisines[i]].push_back({foods[i], ratings[i]});
        }
    }

    void changeRating(string food, int newRating) {
        for (auto &s : foodmap) {
            for (int i = 0; i < s.second.size(); i++) {
                if (s.second[i].first == food) {
                    s.second[i].second = newRating;
                    break;
                }
            }
        }
    }

    string highestRated(string cuisine) {
        if (foodmap.find(cuisine) == foodmap.end()) return ""; // 如果菜系不存在，返回空字符串

        int maxRating = -1;
        string res = "";

        for (const auto &pair : foodmap[cuisine]) {
            if (pair.second > maxRating || (pair.second == maxRating && pair.first < res)) {
                maxRating = pair.second;
                res = pair.first;
            }
        }

        return res;
    }
};
class Solution1422 {
public:
    int maxScore(string s) {
        int score = s[0] == '0' ? 1 : 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '1') score++;
        }
        int maxScore = score;
        for (int i = 1; i < s.size() - 1; i++) {
            if (s[i] == '0') {
                score++;
                maxScore = max(score, maxScore);
            }
            if (s[i] == '1') score--;
        }
        return score;
    }
};
class Solution852 {
public:
    int peakIndexInMountainArray(vector<int> &arr) {
        int left = 0, right = arr.size() - 2;
        int ans = -1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (arr[middle] > arr[middle + 1]) {
                right = middle - 1;
                ans = middle;
            }
            else { left = middle + 1; }
        }
        return ans;
    }
};
class Solution2586 {
public:
    bool yy(string &s) {
        int count = 0;
        for (auto yy : {'a', 'e', 'i', 'o', 'u'}) {
            if (s[0] == yy) { count++; }
            if (s[s.size() - 1] == yy) { count++; }
            if (count == 2) return true;
        }
        return false;
    }
    int vowelStrings(vector<string> &words, int left, int right) {
        int count = 0;
        for (int i = left; i <= right; i++) {
            if (yy(words[i])) count++;
        }
        return count;
    }
};
class Solution503 {
public:
    vector<int> nextGreaterElements(vector<int> &nums) {
        stack<int> st;
        vector<int> res(nums.size(), -1);
        int n = nums.size();
        for (int i = 0; i < 2 * n; i++) {
            if (!st.empty() && nums[st.top()] < nums[i % n]) {
                res[st.top()] = nums[i % n];
                st.pop();
            }
            st.push(i % n);
        }
        return res;
    }
};

/**
 * @brief 回文串系列
 *
 */
class Solution132 {
public:
    int minCut(string s) {
        int n = s.size();
        // 预计算回文子串
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    if (len <= 2 || dp[i + 1][j - 1]) { dp[i][j] = true; }
                }
            }
        }

        // 计算最小分割次数
        vector<int> cuts(n, INT_MAX);
        for (int i = 0; i < n; i++) {
            if (dp[0][i]) { cuts[i] = 0; }
            else {
                if (cuts[i] == INT_MAX) {
                    for (int j = 0; j < i; j++) {
                        if (dp[j + 1][i]) cuts[i] = min(cuts[i], cuts[j] + 1);
                    }
                }
            }
        }
        return cuts[n - 1];
    }
};

class Solution1278 {
public:
    int palindromePartition(string s, int k) {
        int n = s.size();
        vector<vector<int>> vminchange(n, vector<int>(n, -1));
        auto minchange = [&](auto &&f, int i, int j) {
            if (i >= j) return 0;
            int &res = vminchange[i][j];
            if (res != -1) { // 之前计算过
                return res;
            }
            return res = f(f, i + 1, j - 1) + (s[i] != s[j]);
        };
        vector<vector<int>> f(n, vector<int>(k + 1, -1));
        auto dfs = [&](auto &&dfs, int r, int k) {
            int &res = f[r][k];
            if (k == 1) { return res = minchange(minchange, 0, r); }
            else {
                if (res != -1) return res;
                res = INT_MAX;
                for (int i = k - 2; i < r; i++) {
                    res = min(res, dfs(dfs, i, k - 1) + minchange(minchange, i + 1, r));
                }
                return res;
            }
        };
        return dfs(dfs, n - 1, k);
    }
};

class Solution1745 {
public:
    bool checkPartitioning(std::string s) {
        int n = s.size();
        // 预处理所有子串是否为回文串
        std::vector<std::vector<bool>> isPalindrome(n, std::vector<bool>(n, false));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {
                if (s[i] == s[j] && (j - i <= 2 || isPalindrome[i + 1][j - 1])) {
                    isPalindrome[i][j] = true;
                }
            }
        }

        // 检查是否可以分割成三个回文子串
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                if (isPalindrome[0][i] && isPalindrome[i + 1][j] && isPalindrome[j + 1][n - 1]) {
                    return true;
                }
            }
        }
        return false;
    }
};
class Solution3_5 {
public:
    string breakPalindrome(string palindrome) {
        if (palindrome.size() == 1) return "";
        for (int i = 0; i < palindrome.size(); i++) {
            if (palindrome[i] > 'a' && (palindrome.size() % 2 == 0 || i != palindrome.size() / 2)) {
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        palindrome[palindrome.size() - 1] = 'b';
        return palindrome;
    }
};
/**
 * @brief 前缀和系列
 *
 */
// lc303
class NumArray {
    vector<int> nums_;
    vector<int> pre_sum;

public:
    NumArray(vector<int> &nums) : nums_(nums) {
        pre_sum.resize(nums_.size());
        pre_sum[0] = nums[0];
        for (int i = 1; i < nums_.size(); i++) { pre_sum[i] += pre_sum[i - 1] + nums_[i]; }
    }

    int sumRange(int left, int right) {
        if (left == 0) return pre_sum[right];
        return pre_sum[right] - pre_sum[left - 1];
    }
};

// 560. 和为 K 的子数组
class Solution560 {
public:
    int subarraySum(vector<int> &nums, int k) {
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 0; i < n; i++) { s[i + 1] = s[i] + nums[i]; }

        int ans = 0;
        unordered_map<int, int> cnt;
        for (int sj : s) {
            ans += cnt[sj - k] ? cnt[sj - k] : 0;
            cnt[sj]++; // 下标小于j的s[j]-k的数目
        }
        return ans;
    }
    int subarraySum2(vector<int> &nums, int k) {
        int ans = 0, preSum = 0;
        unordered_map<int, int> cnt{{0, 1}}; // s[0]=0 单独统计
        for (int x : nums) {
            preSum += x;
            ans += cnt[(preSum - k)] ? cnt[preSum - k] : 0;
            cnt[preSum]++;
        }
        return ans;
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/subarray-sum-equals-k/solutions/2781031/qian-zhui-he-ha-xi-biao-cong-liang-ci-bi-4mwr/
// lc2588 美丽的子数组
class lc2588 {
public:
    long long beautifulSubarrays(vector<int> &nums) {
        int ans = 0, pre = 0;
        unordered_map<int, int> cnt{{0, 1}};
        for (int x : nums) {
            pre ^= x;
            ans += cnt[pre] ? cnt[pre] : 0;
            cnt[pre]++;
        }
        return ans;
    }
};
// 128 最长连续序列

class Solution2 {
public:
    int count = 0;
    unordered_map<int, int> umap;
    void back(vector<int> &nums, int k, int start) {
        if (start >= nums.size()) { return; }
        for (int i = start; i < nums.size(); i++) {
            if (umap[nums[i] - k] == 0 && umap[nums[i] + k] == 0) {
                count++;
                umap[nums[i]]++;
                back(nums, k, i + 1);
                umap[nums[i]]--;
            }
        }
    }
    int beautifulSubsets(vector<int> &nums, int k) {
        back(nums, k, 0);
        return count;
    }
};

class Solution2597 {
public:
    int beautifulSubsets(vector<int> &nums, int k) {
        unordered_map<int, map<int, int>> groups;
        for (int x : nums) {
            // 模 k 同余的数分到同一组，记录元素 x 及其出现次数
            groups[x % k][x]++;
        }

        int ans = 1;
        for (auto &[_, cnt] : groups) {
            // 计算这一组的方案数
            auto it = cnt.begin();
            int f0 = 1, f1 = 1 << it->second;
            for (it++; it != cnt.end(); it++) {
                auto [x, c] = *it;
                int new_f = x - prev(it)->first == k ? f1 + f0 * ((1 << c) - 1) : f1 << c;
                f0 = f1;
                f1 = new_f;
            }
            ans *= f1; // 每组方案数相乘
        }
        return ans - 1; // 去掉空集
    }

    int beautifulSubsets2(vector<int> &nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums) { cnt[x]++; }

        int ans = 1;
        for (auto &[x, times] : cnt) {
            if (cnt.find(x - k) != cnt.end()) { // x 不是等差数列的首项
                continue;
            }
            // 计算这一组的方案数
            int f0 = 1, f1 = 1 << times;
            for (int y = x + k; cnt.find(y) != cnt.end(); y += k) {
                int new_f = f1 + f0 * ((1 << cnt[y]) - 1);
                f0 = f1;
                f1 = new_f;
            }
            ans *= f1; // 每组方案数相乘
        }
        return ans - 1; // 去掉空集
    }
};

class Solutionf {
public:
    long long maximumBeauty(vector<int> &flowers, long long newFlowers, int target, int full,
                            int partial) {
        int n = flowers.size();

        // 如果全部种满，还剩下多少朵花？
        long long left_flowers = newFlowers - 1LL * target * n; // 先减掉
        for (int &flower : flowers) {
            flower = min(flower, target);
            left_flowers += flower; // 把已有的加回来
        }

        // 没有种花，所有花园都已种满
        if (left_flowers == newFlowers) {
            return 1LL * n * full; // 答案只能是 n*full（注意不能减少花的数量）
        }

        // 可以全部种满
        if (left_flowers >= 0) {
            // 两种策略取最大值：留一个花园种 target-1 朵花，其余种满；或者，全部种满
            return max(1LL * (target - 1) * partial + 1LL * (n - 1) * full, 1LL * n * full);
        }

        sort(flowers.begin(), flowers.end()); // 时间复杂度的瓶颈在这，尽量写在后面

        long long ans = 0, pre_sum = 0;
        int j = 0;
        // 枚举 i，表示后缀 [i, n-1] 种满（i=0 的情况上面已讨论）
        for (int i = 1; i <= n; i++) {
            // 撤销，flowers[i-1] 不变成 target
            left_flowers += target - flowers[i - 1];
            if (left_flowers < 0) { // 花不能为负数，需要继续撤销
                continue;
            }

            // 满足以下条件说明 [0, j] 都可以种 flowers[j] 朵花
            while (j < i && 1LL * flowers[j] * j <= pre_sum + left_flowers) {
                pre_sum += flowers[j];
                j++;
            }

            // 计算总美丽值
            // 在前缀 [0, j-1] 中均匀种花，这样最小值最大
            long long avg =
                (left_flowers + pre_sum) / j; // 由于上面特判了，这里 avg 一定小于 target
            long long total_beauty = avg * partial + 1LL * (n - i) * full;
            ans = max(ans, total_beauty);
        }

        return ans;
    }
};
// 2070. 每一个查询的最大美丽值
class Solution2070 {
public:
    //  在线算法，遍历queries，但这里有个技巧，先按照价格sort一下items，后面能二分，从而降低时间复杂度n^2
    //  -> (n+m)log n
    vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries) {
        sort(items.begin(), items.end());
        // 预处理：计算前缀最大值
        for (int i = 1; i < items.size(); i++) { items[i][1] = max(items[i][1], items[i - 1][1]); }
        // 处理每个查询
        vector<int> res(queries.size(), 0);
        for (int i = 0; i < queries.size(); i++) {
            int left = 0, right = items.size() - 1;
            int maxBeauty = 0;
            // 二分查找
            while (left <= right) {
                int middle = left + (right - left) / 2;
                if (items[middle][0] <= queries[i]) {
                    maxBeauty = items[middle][1]; // 更新最大值
                    left = middle + 1;            // 继续向右查找
                }
                else {
                    right = middle - 1; // 向左查找
                }
            }
            res[i] = maxBeauty;
        }
        return res;
    }
    // 离线算法 把 queries 排序，通过改变回答询问的顺序，使问题更容易处理。
    vector<int> maximumBeauty2(vector<vector<int>> &items, vector<int> &queries) {
        // 对 items 按照价格进行排序
        sort(items.begin(), items.end(),
             [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });

        // 创建查询索引数组，并按照查询值排序
        vector<int> idx(queries.size());
        iota(idx.begin(), idx.end(), 0); // 填充索引 0, 1, 2, ..., n-1
        sort(idx.begin(), idx.end(), [&](int i, int j) { return queries[i] < queries[j]; });

        // 处理查询
        vector<int> ans(queries.size());
        int max_beauty = 0, j = 0;
        for (int i : idx) {
            int q = queries[i];
            // 增量地遍历满足 price <= q 的物品，更新最大美丽值
            while (j < items.size() && items[j][0] <= q) {
                max_beauty = max(max_beauty, items[j][1]);
                j++;
            }
            ans[i] = max_beauty;
        }

        return ans;
    }
    // 链接：https://leetcode.cn/problems/most-beautiful-item-for-each-query/solutions/1100468/jiang-xun-wen-chi-xian-pai-xu-by-endless-o5j0/
};
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 2269. 找到一个数字的 K 美丽值
class Solution2269 {
public:
    int divisorSubstrings(int num, int k) {
        string s = to_string(num);
        int count = 0;
        for (int i = 0; i <= s.size() - k; i++) {
            int subint = stoi(s.substr(i, k));
            if (subint != 0 && num % subint == 0) count++;
        }
        return count;
    }
};


int main() {
    vector<int> a{100, 4, 200, 1, 3, 2};
}