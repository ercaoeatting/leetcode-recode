#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class lc509 {
public:
    int fib(int n) {
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        if (n < 2) return n; // 防空指针，也是剪枝
        for (int i = 2; i <= n; i++) { dp[i] = dp[i - 1] + dp[i - 2]; }
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
        for (int i = 3; i <= n; i++) { dp[i] = dp[i - 1] + dp[i - 2]; }
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
            for (int j = 1; j < n; j++) { dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; }
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
                if (obstacleGrid[i][j]) { dp[i][j] = 0; }
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
            for (int j = 0; j < i; j++) { dp[i] += dp[j] * dp[i - j - 1]; }
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
        for (int i = 0; i < index; ++i) { cin >> weight[i]; }
        for (int j = 0; j < index; ++j) { cin >> value[j]; }
        vector<vector<int>> dp(index, vector<int>(bagweight + 1, 0));
        for (int j = weight[0]; j <= bagweight; j++) dp[0][j] = value[0];
        for (int i = 1; i < weight.size(); i++) {
            for (int j = 1; j <= bagweight; j++) {
                if (j < weight[i])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] =
                        max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]); // 核心转移公式
            }
        }
        cout << dp[index - 1][bagweight];
        ;
    }
    void deal(int M, int bagweight) {
        vector<int> weight(M, 0);
        vector<int> value(M, 0);
        for (int i = 0; i < M; i++) { cin >> weight[i]; }
        for (int j = 0; j < M; j++) { cin >> value[j]; }
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
        for (int i = 0; i < nums.size(); i++) { sum += nums[i]; }
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
        for (int i = 0; i < nums.size(); i++) { sum += nums[i]; }
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
            for (int j = (sum + target) / 2; j >= nums[i]; j--) { dp[j] += dp[j - nums[i]]; }
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
                if (c == '0')
                    n0++;
                else
                    n1++;
            }
            for (int i = m; i >= n0; i--) {
                for (int j = n; j >= n1; j--) { dp[i][j] = max(dp[i][j], dp[i - n0][j - n1] + 1); }
            }
        }
        return dp[m][n];
    }
};

class lc518 {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) { dp[j] += dp[j - coins[i]]; }
        }
        return dp[amount];
    }
};
int main() { vector<string> a{"10", "0001", "111001", "1", "0"}; }