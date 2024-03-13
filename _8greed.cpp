#include <algorithm>
#include <vector>
using namespace std;
// 分发饼干
class lc455 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int count = 0;
        for (int i = g.size() - 1, j = s.size() - 1; i >= 0; i--) {
            if (j >= 0 && s[j] >= g[i]) {
                count++;
                j--;
            }
        }
        return count;
    }
};
// 摆动序列
class lc376 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() == 1) return 1;

        int count = 1;
        int predif = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            int curdif = nums[i + 1] - nums[i];
            if ((predif >= 0 && curdif < 0) || (predif <= 0 && curdif > 0)) {
                count++;
                predif = curdif;
            }
        }
        return count;
    }
};
// 最大子序和
class lc53 {
public:
    // 贪心：当前“连续和”为负数的时候立刻放弃，从下一个元素重新计算“连续和”
    int maxSubArray(vector<int>& nums) {
        int result = INT32_MIN;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i];
            if (count > result) { // 取区间累计的最大值（相当于不断确定最大子序终止位置）
                result = count;
            }
            if (count <= 0) count = 0; // 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
        }
        return result;
    }
};
// 买卖股票的最佳时机II
class lc122 {
public:
    // 局部最优：收集每天的正利润
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for (int i = 1; i < prices.size(); i++) { result += max(0, prices[i] - prices[i - 1]); }
        return result;
    }
};
// 跳跃游戏
class lc55 {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (cover >= i) cover = max(cover, i + nums[i]);
        }
        return cover > nums.size() - 1;
    }
};
