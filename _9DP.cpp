#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
class lc509 {
public:
    int fib(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        if (n < 2) return n; // 防空指针，也是剪枝
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
class lc70 {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1);
        if (n <= 2) return n;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
    // 依然可以优化空间复杂度
    class Solution {
    public:
        int climbStairs(int n) {
            if (n <= 1) return n;
            int dp[3];
            dp[1] = 1;
            dp[2] = 2;
            for (int i = 3; i <= n; i++) {
                int sum = dp[1] + dp[2];
                dp[1] = dp[2];
                dp[2] = sum;
            }
            return dp[2];
        }
    };
};
class kama_57 {
public:
    int goupstairs(int n, int m) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) { // 把m换成2，就可以AC爬楼梯这道题
                if (i - j >= 0) dp[i] += dp[i - j];
            }
        }
        return dp[n];
    }
};
class lc746 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        if (cost.size() == 1) return cost[0];
        vector<int> dp(cost.size() + 1);
        dp[0] = 0;
        dp[1] = 0;
        for (int i = 2; i <= cost.size(); i++) {
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[cost.size()];
    }
};
// 不同路径
class lc62 {
public:
    int uniquePaths(int m, int n) {
        int dp[m][n];
        for (int i = 0; i < m; i++) dp[i][0] = 1;
        for (int i = 0; i < n; i++) dp[0][i] = 1;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
// 不同路径II
class lc63 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        int dp[m][n];
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
            if (obstacleGrid[i][0]) {
                for (int j = i; j < m; j++) dp[j][0] = 0;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
            if (obstacleGrid[0][i]) {
                for (int j = i; j < n; j++) dp[0][j] = 0;
                break;
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                if (obstacleGrid[i][j]) {
                    dp[i][j] = 0;
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};
// 整数拆分
class lc343 {
public:
    int integerBreak(int n) {
        int dp[n + 1];
        memset(dp, 0, sizeof(int) * (n + 1));
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 1; j <= i / 2; j++) {
                dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
            }
        }
        return dp[n];
    }
};
// 有多少二叉搜索树
class lc96 {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                dp[i] += dp[j] * dp[i - j - 1];
            }
        }
        return dp[n];
    }
};
// 0-1背包
class kama_46 {
public:
    void pack(int index, int bagweight) {
        vector<int> weight(index, 0); // 存储每件物品所占空间
        vector<int> value(index, 0);  // 存储每件物品价值
        for (int i = 0; i < index; ++i) {
            cin >> weight[i];
        }
        for (int j = 0; j < index; ++j) {
            cin >> value[j];
        }
        vector<vector<int>> dp(index, vector<int>(bagweight + 1, 0));
        for (int j = weight[0]; j <= bagweight; j++) dp[0][j] = value[0];
        for (int i = 1; i < weight.size(); i++) {
            for (int j = 1; j <= bagweight; j++) {
                if (j < weight[i])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] +
                                                     value[i]); // 核心转移公式
            }
        }
        cout << dp[index - 1][bagweight];
        ;
    }
    void deal(int M, int bagweight) {
        vector<int> weight(M, 0);
        vector<int> value(M, 0);
        for (int i = 0; i < M; i++) {
            cin >> weight[i];
        }
        for (int j = 0; j < M; j++) {
            cin >> value[j];
        }
        vector<int> dp(bagweight + 1, 0);
        for (int i = 0; i < M; i++) {
            for (int j = bagweight; j >= weight[i]; j--) {
                dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
            }
        }
        std::cout << dp[bagweight] << std::endl;
    }
};
class lc416 {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (sum % 2 != 0) return false;
        vector<int> dp(sum / 2 + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = sum / 2; j >= nums[i]; j--) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        return dp[sum / 2] == sum / 2;
    }
};

class lc1049 {
public:
    int lastStoneWeightII(vector<int>& nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        if (sum % 2 != 0) return false;
        vector<int> dp(sum / 2 + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = sum / 2; j >= nums[i]; j--) {
                // sum/2 和+1都行，因为2 3 和3 2 最后输出都是1
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        return abs(2 * dp[sum / 2] - sum);
    }
};
class lc494 {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int k : nums) sum += k;
        if (abs(target) > sum) return 0;
        if ((target + sum) % 2 == 1) return 0;
        vector<int> dp((target + sum) / 2 + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = (sum + target) / 2; j >= nums[i]; j--) {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[(target + sum) / 2];
    }
};

class lc474 {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (string s : strs) {
            int n0 = 0, n1 = 0;
            for (char c : s) {
                if (c == '0') {
                    n0++;
                } else {
                    n1++;
                }
            }
            for (int i = m; i >= n0; i--) {
                for (int j = n; j >= n1; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - n0][j - n1] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
// 完全背包
// 零钱兑换II
class lc518 {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount];
    }
};
// 组合总和IV
class lc377 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int j = 0; j <= target; j++) {
            for (int i = 0; i < nums.size(); i++) {
                if (j >= nums[i] && dp[j] < INT_MAX - dp[j - nums[i]])
                    dp[j] += dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};
// 零钱兑换
class lc322 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                if (dp[j - coins[i]] != INT_MAX)
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
        return dp[amount];
    }
};
// 完全平方数
class lc279 {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; i++) {         // 遍历背包
            for (int j = 1; j * j <= i; j++) { // 遍历物品
                dp[i] = min(dp[i - j * j] + 1, dp[i]);
            }
        }
        return dp[n];
    }
};
// 单词拆分
class lc139 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        unordered_set<string> word(wordDict.begin(), wordDict.end());
        for (int j = 1; j <= s.size(); j++) {
            for (int i = 0; i < j; i++) {
                if (dp[j]) break; // 剪枝操作
                if (!dp[i]) continue;
                string substr = s.substr(i, j - i);
                if (word.find(substr) != word.end() && dp[i]) {
                    dp[j] = true;
                }
            }
        }
        return dp[s.size()];
    }
};
// 打家劫舍1
class lc198 {
public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        if (size == 2) {
            return max(nums[0], nums[1]);
        }
        vector<int> dp(size, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[size - 1];
    }
};
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class lc152 {
public:
    int maxProduct(vector<int>& nums) {
        vector<vector<int>> dp(nums.size() + 1, vector<int>(2, 0));
        // dp[i][0] 最小值   dp[i][1] 最大值
        dp[0][0] = nums[0];
        dp[0][1] = nums[0];
        int res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] >= 0) {
                dp[i][1] = max(dp[i - 1][1] * nums[i], nums[i]);
                dp[i][0] = min(dp[i - 1][0] * nums[i], nums[i]);
                res = max(dp[i][1], res);
            } else {
                dp[i][1] = max(dp[i - 1][0] * nums[i], nums[i]);
                dp[i][0] = min(dp[i - 1][1] * nums[i], nums[i]);
                res = max(dp[i][1], res);
            }
        }
        return res;
    }
};
class m17_16 {
public:
    int massage(vector<int>& nums) {
        int size = nums.size();
        if (size == 0) return 0;
        if (size == 1) return nums[0];
        if (size == 2) return max(nums[0], nums[1]);
        vector<int> dp(size, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[size - 1];
    }
};

class lc337 {
public:
    unordered_map<TreeNode*, int> umap; // 节点，结果
    int rob_bt(TreeNode* root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return root->val;
        if (umap[root]) return umap[root];
        // 抢劫父节点
        int val1 = root->val;
        if (root->left)
            val1 += rob_bt(root->left->left) +
                    rob_bt(root->left->right); // 不考虑左子
        if (root->right)
            val1 += rob_bt(root->right->left) +
                    rob_bt(root->right->right); // 不考虑右子
        // 不抢劫父节点
        int val2 = rob_bt(root->left) + rob_bt(root->right);
        umap[root] = max(val1, val2); // 记忆化
        return max(val1, val2);
    }
    vector<int> robTree(TreeNode* cur) {
        if (cur == nullptr) return vector<int>{0, 0};
        // dp[k][0]不偷该节点所得到的的最大金钱，dp[k][1]记录偷该节点所得到的的最大金钱。
        vector<int> left = robTree(cur->left);
        vector<int> right = robTree(cur->right);
        int val1 = cur->val + left[0] + right[0]; // 偷当前节点
        int val2 = max(left[0], left[1]) +
                   max(right[0], right[1]); // 不偷当前节点，“考虑”偷子节点
        return {val1, val2};
    }
    int rob(TreeNode* root) {
        vector<int> res = robTree(root);
        return max(res[0], res[1]);
    }
};
// 买股票
// 一次买卖
class lc121 {
public:
    // 贪心
    int maxProfit_t(vector<int>& prices) {
        int minp = prices[0], res = 0;
        for (int i : prices) {
            minp = min(minp, i);
            res = max(res, i - minp);
        }
        return res;
    }
    // DP
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        // dp[k][0] 不持有 [1]持有 dp[i][0] 表示第i天不持有股票所得最多现金
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], -prices[i]);
        }
        return dp[prices.size() - 1][0];
    }
    // 滚动数组压缩
    int maxProfit_zip(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(
            2, vector<int>(2)); // 注意这里只开辟了一个2 * 2大小的二维数组
        dp[0][0] -= prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < len; i++) {
            dp[i % 2][0] = max(dp[(i - 1) % 2][0], -prices[i]);
            dp[i % 2][1] =
                max(dp[(i - 1) % 2][1], prices[i] + dp[(i - 1) % 2][0]);
        }
        return dp[(len - 1) % 2][1];
    }
};
// 多次买卖
class LC122 {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(
            2, vector<int>(2)); // 注意这里只开辟了一个2 * 2大小的二维数组
        dp[0][0] -= prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < len; i++) {
            // 两个状态             i-1持有股票          i-1不持有股票
            dp[i % 2][0] = max(dp[(i - 1) % 2][0],
                               dp[(i - 1) % 2][1] - prices[i]); // dp [0]持有
            dp[i % 2][1] = max(dp[(i - 1) % 2][1],
                               prices[i] + dp[(i - 1) % 2][0]); // 不持有
        }
        return dp[(len - 1) % 2][1];
    }
};
// 两次买卖
class lc123 {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len, vector<int>(5));
        // 0 不操作 1第一次持有 2第一次不持有 3第二次持有 4第二次不持有
        dp[0][1] = -prices[0];
        dp[0][2] = 0;
        dp[0][3] = -prices[0];
        dp[0][4] = 0;
        for (int i = 1; i < len; i++) {
            dp[i][1] = max(dp[i - 1][1], -prices[i]); // 第1次持有
            dp[i][2] =
                max(dp[i - 1][2], dp[i - 1][1] + prices[i]); // 第1次不持有
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]); // 第2次持有
            dp[i][4] =
                max(dp[i - 1][4], dp[i - 1][3] + prices[i]); // 第2次不持有
        }
        return dp[len - 1][4];
    }
};
// k次买卖
class lc188 {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
        // dp[1] 第一次持有  dp[2] 1no  dp[3]2have
        for (int i = 0; i < k; i++) {
            dp[0][2 * i + 1] = -prices[0];
        }
        for (int i = 1; i < prices.size(); i++) {
            for (int j = 0; j < 2 * k - 1; j += 2) {
                dp[i][j + 1] =
                    max(dp[i - 1][j + 1], dp[i - 1][j] - prices[i]); // 持有
                dp[i][j + 2] = max(dp[i - 1][j + 2],
                                   dp[i - 1][j + 1] + prices[i]); // 不持有
            }
        }
        return dp[prices.size() - 1][2 * k];
    }
};
// 冷冻期
class lc309 {
public:
    template <typename Fn, typename... Args>
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(4, 0));
        dp[0][0] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i % 2][0] =
                max(dp[(i - 1) % 2][0], max(dp[(i - 1) % 2][1] - prices[i],
                                            dp[(i - 1) % 2][3] - prices[i]));
            dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][3]);
            dp[i % 2][2] = dp[(i - 1) % 2][0] + prices[i];
            dp[i % 2][3] = dp[(i - 1) % 2][2];
        }
        return max(dp[(prices.size() - 1) % 2][1],
                   max(dp[(prices.size() - 1) % 2][2],
                       dp[(prices.size() - 1) % 2][3]));
    }
};
// 最长递增子序列
class lc300 {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        vector<int> dp(nums.size(), 0);
        dp[0] = 1;
        int result = 0;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            result = (dp[i] > result) ? dp[i] : result;
        }
        return result;
    }
    // 维护优化时间复杂度O(N)O(logN)
    int lengthOfLIS2(vector<int>& nums) {
        vector<int> p{nums[0]};
        for (int i = 1; i < nums.size(); i++) {
            if (auto num = nums[i]; num > p.back())
                p.push_back(num);
            else {
                auto j = lower_bound(p.begin(), p.end(), num);
                *j = num;
            }
        }
        return p.size();
    }
    // 等价于
    int Searchupnum(vector<int>& p, int num) {
        int left = 0, right = p.size(); // 区间[left,right）
        while (left < right) {          // [2,3)是有效区间，包含2
            int middle = left + (right - left) / 2;
            if (p[middle] >= num) // 答案在 [left, mid)
                right = middle;
            else
                left = middle + 1; // 答案在 [mid+1, right)
        }
        return left; // 此时left == right，指向第一个 >= target 的位置
    }
    int lengthOfLIS3(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int> p{nums[0]};
        for (int i = 1; i < nums.size(); i++) {
            int num = nums[i];
            if (num > p.back()) {
                p.push_back(num);
            } else {
                // 使用手写的二分查找替代 lower_bound
                int j = Searchupnum(p, num);
                p[j] = num;
            }
        }
        return p.size();
    }
};

int main() {}