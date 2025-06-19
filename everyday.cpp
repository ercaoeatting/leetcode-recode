#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
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
            if (s[i] == 'i') {
                reverse(res);
            } else {
                res.push_back(s[i]);
            }
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
            if ((*it) == key) {
                return true;
            }
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
        if (check_.empty()) {
            can.push_back({0, n_ - 1});
        } else {
            int begin1 = check_[0][0];
            int end1 = check_[0][1];
            if (begin1 > 0) {
                can.push_back({0, begin1 - 1});
            }
            for (int i = 1; i < check_.size(); i++) {
                int begin2 = check_[i][0];
                int end2 = check_[i][1];
                if (begin2 > end1 + 1) can.push_back({end1 + 1, begin2 - 1});
                begin1 = begin2;
                end1 = end2;
            }
            if (end1 < n_ - 1) {
                can.push_back({end1 + 1, n_ - 1});
            }
        }
        for (auto &block : can) {
            int start = block[0];
            int end = block[1];
            int available_size = end - start + 1;
            if (available_size >= size) {
                // 分配内存，并插入到 check_ 的正确位置以保持有序
                vector<int> new_block = {start, start + size - 1, mID};
                auto insert_pos = lower_bound(check_.begin(), check_.end(), new_block,
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
                for (int i = (*it)[0]; i <= (*it)[1]; i++) {
                    array_[i] = 0;
                }
                it = check_.erase(it); // 从 check_ 中移除该内存块
                count++;
            } else {
                it++;
            }
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
            if (memory[i]) {
                count = 0;
            } else {
                ++count;
                if (count == size) {
                    for (int j = i - count + 1; j <= i; ++j) {
                        memory[j] = mID;
                    }
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
        while (!stack2.empty()) {
            stack2.pop();
        }
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
        for (char c : text) {
            texts.insert(cursor, c);
        }
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
        while (cursor != texts.begin() && k--) {
            cursor = prev(cursor);
        }
        auto head = cursor;
        for (int i = 0; i < 10 && head != texts.begin(); i++) {
            head = prev(head);
        }
        return string(head, cursor);
    }

    string cursorRight(int k) {
        while (cursor != texts.end() && k--) {
            cursor = next(cursor);
        }
        auto head = cursor;
        for (int i = 0; i < 10 && head != texts.begin(); i++) {
            head = prev(head);
        }
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
            } else {
                left = middle + 1;
            }
        }
        return ans;
    }
};
class Solution2586 {
public:
    bool yy(string &s) {
        int count = 0;
        for (auto yy : {'a', 'e', 'i', 'o', 'u'}) {
            if (s[0] == yy) {
                count++;
            }
            if (s[s.size() - 1] == yy) {
                count++;
            }
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
                    if (len <= 2 || dp[i + 1][j - 1]) {
                        dp[i][j] = true;
                    }
                }
            }
        }

        // 计算最小分割次数
        vector<int> cuts(n, INT_MAX);
        for (int i = 0; i < n; i++) {
            if (dp[0][i]) {
                cuts[i] = 0;
            } else {
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
            if (k == 1) {
                return res = minchange(minchange, 0, r);
            } else {
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
        for (int i = 1; i < nums_.size(); i++) {
            pre_sum[i] += pre_sum[i - 1] + nums_[i];
        }
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
        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + nums[i];
        }

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
        if (start >= nums.size()) {
            return;
        }
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
        for (int x : nums) {
            cnt[x]++;
        }

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
    long long maximumBeauty(vector<int> &flowers, long long newFlowers, int target, int full, int partial) {
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
            // 两种策略取最大值：留一个花园种 target-1
            // 朵花，其余种满；或者，全部种满
            return max(1LL * (target - 1) * partial + 1LL * (n - 1) * full, 1LL * n * full);
        }

        sort(flowers.begin(),
             flowers.end()); // 时间复杂度的瓶颈在这，尽量写在后面

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
            long long avg = (left_flowers + pre_sum) / j; // 由于上面特判了，这里 avg 一定小于 target
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
        for (int i = 1; i < items.size(); i++) {
            items[i][1] = max(items[i][1], items[i - 1][1]);
        }
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
                } else {
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
        sort(items.begin(), items.end(), [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });

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

class Solution2012 {
public:
    int sumOfBeauties(vector<int> &nums) {
        int n = nums.size();
        vector<int> sufMin(n, 0);
        int preMax = nums[0];
        sufMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i > 0; i--) {
            sufMin[i] = min(sufMin[i + 1], nums[i]);
        }
        int ans = 0;
        for (int i = 1; i < n - 1; i++) {
            preMax = max(preMax, nums[i - 1]);
            if (nums[i] > preMax && nums[i] < sufMin[i + 1]) {
                ans += 2;
            } else if (nums[i] > nums[i - 1] && nums[i] < nums[i + 1]) {
                ans += 1;
            }
        }
        return ans;
    }
};

// 3305. 元音辅音字符串计数 I
class Solution3305 {
    bool check(char &c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }

public:
    long long f(string word, int k) {
        vector<long long> cut('u' - 'a' + 1, 0);
        long long i = 0;
        int k_count = 0;
        long long ans = 0;
        for (char c : word) {
            if (check(c)) {
                cut[c - 'a']++;
            } else {
                k_count++;
            }
            while (cut[0] > 0 && cut['e' - 'a'] > 0 && cut['i' - 'a'] > 0 && cut['o' - 'a'] > 0 && cut['u' - 'a'] > 0 &&
                   k_count >= k) {
                if (check(word[i])) {
                    cut[word[i] - 'a']--;
                } else {
                    k_count--;
                }
                i++;
            }
            ans += i;
        }
        return ans;
    }
    long long countOfSubstrings(string word, int k) { return f(word, k) - f(word, k + 1); }
};

// 3340. 检查平衡字符串
class Solution3340 {
public:
    bool isBalanced(string num) {
        int s = 0;
        for (int i = 0; i < num.size(); i++) {
            s += (i % 2 == 1) ? num[i] - '0' : '0' - num[i];
        }
        return s == 0;
    }
};
// 2272. 最大波动的子字符串
class Solution2272 {
public:
    int largestVariance(string s) {
        int ans = 0;
        unordered_map<char, int> umap;
        for (char c : s) {
            umap[c]++;
        }
        for (char a = 'a'; a <= 'z'; a++) {
            for (char b = 'a'; b <= 'z'; b++) {
                if (b == a) {
                    continue;
                }
                if (umap[a] == 0 || umap[b] == 0) continue;
                int f0 = 0, f1 = INT_MIN;
                for (char ch : s) {
                    if (ch == a) {
                        f0 = max(f0, 0) + 1;
                        f1++;
                    } else if (ch == b) {
                        f1 = f0 = max(f0, 0) - 1;
                    } // else f0 = max(f0, 0); 可以留到 ch 等于 a 或者 b
                      // 的时候计算，f1 不变
                    ans = max(ans, f1);
                }
            }
        }
        return ans;
    }
    class Solution {
    public:
        int largestVariance(string s) {
            int ans = 0;
            int f0[26][26]{}, f1[26][26];
            memset(f1, -0x3f, sizeof(f1)); // 初始化成一个很小的负数
            for (char ch : s) {
                ch -= 'a';
                // 遍历到 ch 时，只需计算 a=ch 或者 b=ch 的状态，其他状态和 ch
                // 无关，f 值不变
                for (int i = 0; i < 26; i++) {
                    if (i == ch) {
                        continue;
                    }
                    // 假设出现次数最多的字母 a=ch，更新所有 b=i 的状态
                    f0[ch][i] = max(f0[ch][i], 0) + 1;
                    f1[ch][i]++;
                    // 假设出现次数最少的字母 b=ch，更新所有 a=i 的状态
                    f1[i][ch] = f0[i][ch] = max(f0[i][ch], 0) - 1;
                    ans = max(ans, max(f1[ch][i],
                                       f1[i][ch])); // 或者 max({ans, f1[ch][i],
                                                    // f1[i][ch]})
                }
            }
            return ans;
        }
    };
};
class canBeValid1 {
    struct st {
        int min;
        int max;
    } st;

public:
    bool canBeValid(string s, string locked) {
        pair<int, int> minmax{0, 0};
        for (int i = 0; i < s.size(); i++) {
            if (locked[i] == '0') {
                if (st.min == 0)
                    st.min = 1;
                else
                    st.min--;
                st.max++;
            } else if (s[i] == '(') {
                st.min++;
                st.max++;
            } else {
                st.min--;
                if (st.min < 0) st.min = 1;
                st.max--;
                if (st.max < 0) return false;
            }
        }
        return st.min == 0;
    }
};

class duijiaoxian {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ans(m, vector<int>(n, 0));
        // k = i - j + n   k + j -n,j 是对角元素   j = i - k + n
        for (int k = 1; k < m + n; k++) {
            int jmin = max(0, n - k);
            int jmax = min(n - 1, m - 1 - k + n);
            unordered_set<int> uset;
            for (int j = jmin; j <= jmax; j++) {
                ans[k + j - n][j] = uset.size();
                uset.insert(grid[k + j - n][j]);
            }
            uset.clear();
            for (int j = jmax; j >= jmin; j--) {
                ans[k + j - n][j] = abs((int)uset.size() - ans[k + j - n][j]);
                uset.insert(grid[k + j - n][j]);
            }
        }
        return ans;
    }
};

// 2716. 最小化字符串长度
class Solution2716 {
public:
    int minimizedStringLength(string s) { return unordered_set<char>(s.begin(), s.end()).size(); }
};
// 2109. 向字符串添加空格
class Solution2109 {
public:
    string addSpaces(string s, vector<int> &spaces) {
        string res(s.size() + spaces.size(), '\0');
        for (size_t i = 0; i < spaces.size(); i++) {
            res[spaces[i] + i] = ' ';
        }
        for (size_t i = 0, is = 0; is < s.size(); i++) {
            if (res[i] == '\0') res[i] = s[is++];
        }

        return res;
    }
};

// 2140. 解决智力问题
class Solution2140 {
public:
    long long mostPoints(vector<vector<int>> &questions) {
        int n = questions.size();
        // dp[j] j...n-1的最高分数
        vector<long long> dp(n, 0);
        dp[n - 1] = questions[n - 1][0];
        for (int i = n - 2; i >= 0; i--) {
            if (i + questions[i][1] + 1 <= n - 1)
                dp[i] = max(dp[i + 1], dp[i + questions[i][1] + 1] + questions[i][0]);
            else
                dp[i] = max(dp[i + 1], (long long)questions[i][0]);
        }
        return dp[0];
    }
    // 简洁的
    class Solution {
    public:
        long long mostPoints(vector<vector<int>> &questions) {
            int n = questions.size();
            vector<long long> f(n + 1);
            for (int i = n - 1; i >= 0; i--) {
                int j = min(i + questions[i][1] + 1, n);
                f[i] = max(f[i + 1], f[j] + questions[i][0]);
            }
            return f[0];
        }
    };

    // 作者：灵茶山艾府
    // 链接：https://leetcode.cn/problems/solving-questions-with-brainpower/solutions/1213919/dao-xu-dp-by-endlesscheng-2qkc/
    // 来源：力扣（LeetCode）
    // 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
};

// 1123. 最深叶节点的最近公共祖先
class Solution1123 {
    int maxdepth = -1;

public:
    int travel(TreeNode *node, int depth, TreeNode *&ans) {
        if (!node) {
            maxdepth = max(maxdepth, depth);
            return depth;
        }
        int ld = travel(node->left, depth + 1, ans);
        int rd = travel(node->right, depth + 1, ans);
        if (ld == rd && ld == maxdepth) ans = node;
        return max(ld, rd);
    }
    TreeNode *lcaDeepestLeaves(TreeNode *root) {
        TreeNode *ans = nullptr;
        travel(root, 0, ans);
        return ans;
    }
};
class Solution1534 {
public:
    int countGoodTriplets(vector<int> &arr, int a, int b, int c) {
        int n = arr.size(), mx = ranges::max(arr), ans = 0;
        vector<int> s(mx + 2, 0); // cnt 数组的前缀和 s[i]为小于等于i-1的cnt
        for (int j = 0; j < arr.size(); j++) {
            int aj = arr[j];
            for (int k = j + 1; k < arr.size(); k++) {
                if (j == 0) break;
                int ak = arr[k];
                if (abs(aj - ak) > b) continue;
                ans += max(s[min({aj + a, ak + c, mx}) + 1] - s[max({aj - a, ak - c, 0})], 0);
            }
            ranges::for_each(s.begin() + aj + 1, s.end(), [](auto &x) { x++; });
        }
        return ans;
    }
};
class Solution258 {
public:
    int addDigits(int num) {
        int ans = num;
        while (ans >= 10) {
            string s = to_string(ans);
            ans = 0;
            for_each(s.begin(), s.end(), [&](auto &x) { ans += x - '0'; });
        }
        return ans;
    }
    int addDigits666(int num) { return (num - 1) % 9 + 1; }
};

class Solution20250405 {
public:
    int ans = 0;
    void travel(vector<int> &nums, int start, int val_tmp) {
        ans += val_tmp;
        if (start >= nums.size()) {
            return;
        }
        for (int i = start; i < nums.size(); i++) {
            travel(nums, i + 1, val_tmp ^ nums[i]);
        }
    }
    int subsetXORSum(vector<int> &nums) {
        if (nums.empty()) return 0;
        travel(nums, 0, 0);
        return ans;
    }
};
class Solution368 {
public:
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<int> ans;
        vector<int> dp(nums.size(), 0);
        vector<int> pre(nums.size(), -1);
        int start = 0;
        int dpmax = -1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0) {
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        pre[i] = j;
                    }
                }
            }
            if (i > 0 && dp[i] > dpmax) {
                dpmax = dp[i];
                start = i;
            }
        }
        if (start == 0) return vector<int>(1, nums[0]);
        ans.push_back(nums[start]);
        while (pre[start] != -1) {
            ans.push_back(nums[pre[start]]);
            start = pre[start];
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    // 超时的回溯
    class Solution {
    public:
        vector<int> tmp;
        vector<int> ans;
        void travel(vector<int> &nums, int start) {
            if (ans.size() < tmp.size()) ans = tmp;
            if (start >= nums.size()) return;
            for (int i = start; i < nums.size(); i++) {
                int flag = 0;
                if (tmp.empty() || nums[i] % tmp.back() == 0) {
                    flag = 1;
                }
                if (flag == 1) tmp.push_back(nums[i]);
                travel(nums, i + 1);
                if (flag == 1) tmp.pop_back();
            }
        }
        vector<int> largestDivisibleSubset(vector<int> &nums) {
            ranges::sort(nums);
            travel(nums, 0);
            return ans;
        }
    };
};

class Solution1281 {
public:
    int subtractProductAndSum(int n) {
        int multiply = 1, add = 0;
        while (n) {
            int loc = n % 10;
            multiply *= loc;
            add += loc;
            n /= 10;
        }
        return multiply - add;
    }
};

// 数位DP
// 902. 最大为 N 的数字组合
class Solution902 {
public:
    int atMostNGivenDigitSet(vector<string> &digits, int n) {
        string n_s = to_string(n);
        int m = n_s.size();
        vector<int> dp(m, -1); // 记忆化缓存
        function<int(int, bool, bool)> dfs = [&](int i, bool islimit, bool isnum) -> int {
            if (i == m) return isnum;                           // 填过数字才算一个有效数字
            if (!islimit && isnum && dp[i] != -1) return dp[i]; // 记忆化

            int res = 0;
            if (!isnum) // 选择跳过当前位（不填数字）
                res += dfs(i + 1, false, false);
            char up = islimit ? n_s[i] : '9'; // 当前位的上限
            for (const string &d : digits) {
                if (d[0] > up) break; // 超过上限，直接停止
                res += dfs(i + 1, islimit && (d[0] == up), true);
            }
            if (!islimit && isnum) dp[i] = res; // 记忆化
            return res;
        };
        return dfs(0, true, false);
    }
};
class Solution2999 {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string s_finish = to_string(finish);
        string s_start = to_string(start);
        s_start = string(s_finish.size() - s_start.size(), '0') + s_start;
        int n = s_finish.size();
        int diff = n - s.size();
        vector<long long> memo(n, -1);
        function<long long(int, bool, bool)> f = [&](int i, bool low, bool high) -> long long {
            if (i == n) return 1;
            if (!low && !high && memo[i] != -1) return memo[i];
            long long res = 0;
            int lo = low ? s_start[i] - '0' : 0;
            int hi = high ? s_finish[i] - '0' : 9;
            if (i < diff) {
                for (int d = lo; d <= min(hi, limit); d++) {
                    res += f(i + 1, low && d == lo, high && d == hi);
                }
            } else {
                int d = s[i - diff] - '0';
                if (d >= lo && d <= hi) {
                    res += f(i + 1, low && d == lo, high && d == hi);
                }
            }
            if (!low && !high) {
                memo[i] = res; // 记忆化 (i,false,false)
            }
            return res;
        };
        return f(0, true, true);
    }
};
class Solution2843 {
public:
    int countSymmetricIntegers(int low, int high) {
        string h = to_string(high);
        string l = to_string(low);
        int n = h.size(), m = n / 2;
        int diff_lh = n - l.size();
        // memo[i][start][diff] start <= start_last, diff+9*m <= 18*m
        vector memo(n, vector(diff_lh + 1, vector<int>(18 * m + 1, -1)));
        function<int(int, int, int, bool, bool)> dfs = [&](int i, int start, int diff, bool low, bool high) -> int {
            if (i == n) return diff == 9 * m;
            if (start != -1 && !low && !high && memo[i][start][diff] != -1) {
                return memo[i][start][diff];
            }
            int lo = low && i >= diff_lh ? l[i - diff_lh] - '0' : 0;
            int hi = high ? h[i] - '0' : 9;

            if (start == -1 && (n - i) % 2) {
                return lo > 0 ? 0 : dfs(i + 1, start, diff, true, false);
            }
            int res = 0;
            bool isleft = start == -1 || i < (start + n) / 2;
            for (int d = lo; d <= hi; d++) {
                res += dfs(i + 1, start == -1 && d > 0 ? i : start, diff + (isleft ? d : -d), low && d == lo,
                           high && d == hi);
            }
            if (start != -1 && !low && !high) {
                memo[i][start][diff] = res;
            }
            return res;
        };
        return dfs(0, -1, 9 * m, true, true);
    }
};

class Solution3272 {
public:
    long long countGoodIntegers(int n, int k) {
        long long ans = 0;
        int base = pow(10, (n - 1) / 2);
        function<int(int)> f;
        f = [&f](int n) -> int { return n == 0 ? 1 : n * f(n - 1); };
        unordered_set<string> uset;
        for (int i = base; i < 10 * base; i++) {
            string s = to_string(i);
            string rev = s.substr(0, s.size() - n % 2);
            reverse(rev.begin(), rev.end());
            s += rev;
            if (stoll(s) % k) { // 回文数不能被 k 整除
                continue;
            }
            ranges::sort(s);
            if (!uset.insert(s).second) { // 不能重复统计
                continue;
            }
            int ump[10]{0};
            for (char x : s) {
                ump[x - '0']++;
            }
            int chu = 1;
            for (int x : ump) {
                chu *= f(x);
            }
            ans += (n - ump[0]) * f(n - 1) / chu;
        }
        return ans;
    }
};
// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/count-good-numbers/solutions/857728/cheng-fa-yuan-li-kuai-su-mi-by-endlessch-btkn/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/count-good-triplets-in-an-array/solutions/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

class Solutioncount_good_triplets {
    template <typename T>
    class FenwickTree {
        vector<T> tree;

    public:
        // 使用下标 1 到 n
        FenwickTree(int n) : tree(n + 1) {}
        // a[i] 增加 val
        // 1 <= i <= n
        void update(int i, T val) {
            for (; i < tree.size(); i += i & -i) {
                tree[i] += val;
            }
        }
        // 求前缀和 a[1] + ... + a[i]
        // 1 <= i <= n
        T pre(int i) const {
            T res = 0;
            for (; i > 0; i &= i - 1) {
                res += tree[i];
            }
            return res;
        }
    };

public:
    long long goodTriplets(vector<int> &nums1, vector<int> &nums2) {
        int n = nums1.size();
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            p[nums1[i]] = i;
        }
        long long ans = 0;
        FenwickTree<int> f(n);
        for (int i = 0; i < n; i++) {
            int y = p[nums2[i]];
            int less = f.pre(y); // 添加一个值为 3 的数，就是调用树状数组的
                                 // update(3,1)。查询小于 3 的元素个数，即小于等于 2
                                 // 的元素个数，就是调用树状数组的 pre(2)
            ans += (long)less * (n - 1 - y - (i - less));
            f.update(y + 1, 1); // y=0....n-1   映射到1.....n
        }
        return ans;
    }
};

class lc1399统计最大数组的数目 {
public:
    int countLargestGroup(int n) {
        string n_s = to_string(n);
        int size = n_s.size();
        vector memo(size, vector(9 * size + 1, -1));

        function<int(int, int, bool)> dfs = [&](int i, int left, bool limit_high) -> int {
            if (i == size) return left == 0;
            if (!limit_high && memo[i][left] != -1) return memo[i][left];
            int res = 0;
            int hi = limit_high ? n_s[i] - '0' : 9;
            for (int d = 0; d <= min(hi, left); d++) {
                res += dfs(i + 1, left - d, limit_high && d == hi);
            }
            if (!limit_high) memo[i][left] = res;
            return res;
        };
        int maxcount = 0;
        int res = 0;
        for (int i = 1; i <= 9 * size; i++) {
            int count = dfs(0, i, true);
            if (count > maxcount) {
                res = 1;
                maxcount = count;
            } else if (count == maxcount)
                res++;
        }
        return res;
    }
};

class 统计定界子数组的数目2444 {
public:
    long long countSubarrays(vector<int> &nums, int minK, int maxK) {
        int minI = -1, maxI = -1, i0 = -1;
        long long ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > maxK || nums[i] < minK) i0 = i;
            if (nums[i] == minK) minI = i;
            if (nums[i] == maxK) maxI = i;
            ans += max(min(minI, maxI) - i0, 0);
        }
        return ans;
    }
};

class 数组的最小相等和2918 {
public:
    long long minSum(vector<int> &nums1, vector<int> &nums2) {
        long long count0_1 = 0, count0_2 = 0;
        long long sum1 = 0, sum2 = 0;
        for (int x : nums1) {
            if (x == 0) count0_1++;
            sum1 += x;
        }
        for (int x : nums2) {
            if (x == 0) count0_2++;
            sum2 += x;
        }
        sum1 += count0_1;
        sum2 += count0_2;
        // 情况1 无法相等
        if ((count0_1 == 0 && sum1 < sum2) || (count0_2 == 0 && sum1 > sum2)) {
            return -1;
        } else if (count0_1 == 0 && count0_2 == 0 && sum1 != sum2) {
            return -1;
        }
        // 情况2 存在没有0的情况
        else if (count0_1 == 0)
            return sum1;
        else if (count0_2 == 0)
            return sum2;
        ;
        // 情况3 都有0
        return max(sum1, sum2);
    }
};

class fastpows {
public:
    static constexpr int MOD = 1'000'000'007;
    static constexpr int SIZE = 26;
    using Matrix = array<array<int, SIZE>, SIZE>;

    Matrix mul(const Matrix &a, const Matrix &b) {
        Matrix res{};
        for (int i = 0; i < SIZE; i++) {
            for (int k = 0; k < SIZE; k++) {
                if (a[i][k] == 0) continue;
                for (int j = 0; j < SIZE; j++) {
                    res[i][j] = (res[i][j] + (long long)a[i][k] * b[k][j]) % MOD;
                }
            }
        }
        return res;
    }
    Matrix fastpow(Matrix base, int n) {
        Matrix res = {};
        for (int i = 0; i < SIZE; i++) {
            res[i][i] = 1; // 单位矩阵
        }
        while (n) {
            if (n & 1) {
                res = mul(res, base);
            }
            base = mul(base, base);
            n >>= 1;
        }
        return res;
    }
    int lengthAfterTransformations(string s, int t, vector<int> &nums) {
        Matrix M{};
        for (int i = 0; i < 26; i++) {
            for (int j = i + 1; j <= i + nums[i]; j++) {
                M[i][j % SIZE] = 1;
            }
        }
        Matrix Mt = fastpow(M, t);
        int ans = 0;
        int F0[26]{0};
        for (char c : s) F0[c - 'a']++;
        for (int i = 0; i < SIZE; i++) {
            ans = (ans + reduce(Mt[i].begin(), Mt[i].end(), 0LL) * F0[i]) % MOD;
        }
        return ans;
    }
};

class 拼车1094 {
public:
    bool carPooling(vector<vector<int>> &trips, int capacity) {
        vector diff(1001, 0);
        for (const auto &trip : trips) {
            int numPassengers = trip[0];
            int from = trip[1];
            int to = trip[2];
            diff[from] += numPassengers;
            diff[to] -= numPassengers;
        }
        int sum_d = 0;
        for (int x : diff) {
            sum_d += x;
            if (sum_d > capacity) return false;
        }
        return true;
    }
};
class 零数组变换II3356 {
public:
    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
        int n = nums.size();
        vector diff(n + 1, 0);
        int sum_d = 0, k = 0; // 双指针
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            sum_d += diff[i];
            while (sum_d < x && k < queries.size()) { // sum_d < x,意味着至少还需要处理一次问询
                int l = queries[k][0];
                int r = queries[k][1];
                int val = queries[k][2];
                diff[l] += val;
                diff[r + 1] -= val;
                if (l <= i && i <= r) { // x 在更新范围中
                    sum_d += val;
                }
                k++;
            }
            if (sum_d < x) return -1;
        }
        return k;
    }
};

class 连接两字母单词得到的最长回文串2131 {
public:
    int longestPalindrome(vector<string> &words) {
        unordered_map<string, int> freq; // 单词出现次数
        for (const string &word : words) {
            ++freq[word];
        }
        int res = 0;      // 最长回文串长度
        bool mid = false; // 是否含有中心单词
        for (const auto &[word, cnt] : freq) {
            // 遍历出现的单词，并更新长度
            string rev = string(1, word[1]) + word[0]; // 反转后的单词
            if (word == rev) {
                if (cnt % 2 == 1) {
                    mid = true;
                }
                res += 2 * (cnt / 2 * 2);
            } else if (word > rev) { // 避免重复遍历
                res += 4 * min(freq[word], freq[rev]);
            }
        }
        if (mid) {
            // 含有中心单词，更新长度
            res += 2;
        }
        return res;
    }
};

class 字典序最末1163 {
public:
    string lastSubstring(string s) {
        int i = 0, j = 1, k = 0;
        int n = s.size();
        while (j + k < n) {
            if (s[i + k] == s[j + k])
                ++k;
            else if (s[i + k] > s[j + k]) {
                j = j + k + 1;
                k = 0;
            } else {
                i = max(j, i + k + 1);
                j = max(i + 1, j);
                k = 0;
            }
        }
        return s.substr(i);
    }
};

// class 按字典序排列最小的等效字符串1061 {
// public:
//     string smallestEquivalentString(string s1, string s2, string baseStr) {
//         int fa[26];
//         ranges::iota(fa, 0);

//         auto find = [&](this auto &&find, int x) -> int {
//             if (fa[x] != x) {
//                 fa[x] = find(fa[x]);
//             }
//             return fa[x];
//         };

//         auto merge = [&](int x, int y) {
//             // 把大的代表元指向小的代表元
//             auto [small, big] = minmax(find(x), find(y));
//             fa[big] = small;
//         };

//         for (int i = 0; i < s1.size(); i++) {
//             merge(s1[i] - 'a', s2[i] - 'a');
//         }

//         for (int i = 0; i < baseStr.size(); i++) {
//             baseStr[i] = find(baseStr[i] - 'a') + 'a';
//         }
//         return baseStr;
//     }
// };

class 划分数组使最大差为K2294 {
public:
    int partitionArray(vector<int> &nums, int k) {
        ranges::sort(nums);
        int res = 1;
        int min = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] - min > k) {
                res++;
                if (i < nums.size() - 1) min = nums[i];
            }
        }
        return res;
    }
};
