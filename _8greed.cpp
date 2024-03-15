#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <list>
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
// K次取反后最大化的数组和
class lc1005 {
    static bool cmp(int a, int b) { return abs(a) > abs(b); }

public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end(), cmp);       // 第一步
        for (int i = 0; i < A.size(); i++) { // 第二步
            if (A[i] < 0 && K > 0) {
                A[i] *= -1;
                K--;
            }
        }
        if (K % 2 == 1) A[A.size() - 1] *= -1; // 第三步
        int result = 0;
        for (int a : A) result += a; // 第四步
        return result;
    }
};
// 加油站
class lc134 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int totalSum = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); i++) {
            curSum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if (curSum < 0) {  // 当前累加rest[i]和 curSum一旦小于0
                start = i + 1; // 起始位置更新为i+1
                curSum = 0;    // curSum从0开始
            }
        }
        if (totalSum < 0) return -1; // 说明怎么走都不可能跑一圈了
        return start;
    }
    // 全局判断
    int lc134_solution2(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int min = INT_MAX; // 从起点出发，油箱里的油量最小值
        for (int i = 0; i < gas.size(); i++) {
            int rest = gas[i] - cost[i];
            curSum += rest;
            if (curSum < min) { min = curSum; }
        }
        if (curSum < 0) return -1; // 情况1
        if (min >= 0)
            return 0; // 情况2
                      // 情况3
        for (int i = gas.size() - 1; i >= 0; i--) {
            int rest = gas[i] - cost[i];
            min += rest;
            if (min >= 0) { return i; }
        }
        return -1;
    }
};
// 分发糖果
// 分而治之，分开贪心的好题目，此题目也是一道hard题，代码不难，精华的是思想
class lc135 {
public:
    int candy(vector<int>& ratings) {
        vector<int> candyVec(ratings.size(), 1);
        // 从前向后
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1]) candyVec[i] = candyVec[i - 1] + 1;
        }
        // 从后向前
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candyVec[i] = max(candyVec[i], candyVec[i + 1] + 1);
            }
        }
        // 统计结果
        int result = 0;
        for (int i = 0; i < candyVec.size(); i++) result += candyVec[i];
        return result;
    }
};
// 柠檬水找零
class lc860 {
public:
    bool find(vector<int>& get, int target) {
        for (auto it = get.begin(); it != get.end(); it++) {
            if (*it == target) {
                get.erase(it);
                return true;
            }
        }
        return false;
    }
    // 蠢!
    bool lemonadeChange(vector<int>& bills) {
        vector<int> get{};
        for (int i = 0; i < bills.size(); i++) {
            get.push_back(bills[i]);
            if (bills[i] == 10 && find(get, 5)) { continue; }
            else if (bills[i] == 10 && !find(get, 5)) { return false; }
            else if (bills[i] == 20) {
                if (find(get, 10) && find(get, 5))
                    continue;
                else if (find(get, 5) && find(get, 5) && find(get, 5))
                    continue;
                else
                    return false;
            }
        }
        return true;
    }
    class Solution {
    public:
        bool lemonadeChange(vector<int>& bills) {
            int five = 0, ten = 0, twenty = 0;
            for (int bill : bills) {
                // 情况一
                if (bill == 5) five++;
                // 情况二
                if (bill == 10) {
                    if (five <= 0) return false;
                    ten++;
                    five--;
                }
                // 情况三
                if (bill == 20) {
                    // 优先消耗10美元，因为5美元的找零用处更大，能多留着就多留着
                    if (five > 0 && ten > 0) {
                        five--;
                        ten--;
                        twenty++; // 其实这行代码可以删了，因为记录20已经没有意义了，不会用20来找零
                    }
                    else if (five >= 3) {
                        five -= 3;
                        twenty++; // 同理，这行代码也可以删了
                    }
                    else
                        return false;
                }
            }
            return true;
        }
    };
};
// 身高重建队列
class lc406 {
    struct cmp {
        bool operator()(vector<int> a, vector<int> b) {
            if (a[0] == b[0]) return a[1] < b[1];
            return a[0] > b[0];
        }
    };

public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp());
        list<vector<int>> list;
        for (int i = 0; i < people.size(); i++) {
            auto it = list.begin();
            int pos = people[i][1];
            while (pos--) { it++; }
            list.insert(it, people[i]);
        }
        return vector<vector<int>>(list.begin(), list.end());
    }
};

int main() {}