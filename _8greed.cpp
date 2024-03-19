#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <list>
#include <string>
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
// mark
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
    // 更好的解法 by 大力王
    class Solution {
    public:
        int wiggleMaxLength(vector<int>& nums) {
            if (nums.size() < 2) return nums.size();
            int pre = 0, res = 1;
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] == nums[i - 1]) continue;
                int cur = (nums[i] > nums[i - 1]) ? 1 : -1;
                res += cur != pre;
                pre = cur;
            }
            return res;
        }
    };
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
// 跳跃游戏II
class lc45 {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int cur = 0, next = 0;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            next = max(next, i + nums[i]); // 下一步“可能”达到的地方
            if (i == cur) {
                ans++;
                cur = next;
            }
            if (cur >= nums.size() - 1) break;
        }
        return ans;
    }
    // 版本二
    class Solution {
    public:
        int jump(vector<int>& nums) {
            int curDistance = 0;  // 当前覆盖的最远距离下标
            int ans = 0;          // 记录走的最大步数
            int nextDistance = 0; // 下一步覆盖的最远距离下标
            for (int i = 0; i < nums.size() - 1; i++) {
                // 注意这里是小于nums.size() - 1，这是关键所在
                nextDistance = max(nums[i] + i, nextDistance); // 更新下一步覆盖的最远距离下标
                if (i == curDistance) {         // 遇到当前覆盖的最远距离下标
                    curDistance = nextDistance; // 更新当前覆盖的最远距离下标
                    ans++;
                }
            }
            return ans;
        }
    };
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
// 引爆气球
class lc452 {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; }

public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; // points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) { // 气球i和气球i-1不挨着，注意这里不是>=
                result++;                          // 需要一支箭
            }
            else {                                                  // 气球i和气球i-1挨着
                points[i][1] = min(points[i - 1][1], points[i][1]); // 更新重叠气球最小右边界
            }
        }
        return result;
    }
};

// 无重叠区间
class lc435 {
public:
    // 按照区间右边界排序
    static bool cmp(const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return 0;
        sort(intervals.begin(), intervals.end(), cmp);
        int count = 1;             // 记录非交叉区间的个数
        int end = intervals[0][1]; // 记录区间分割点
        for (int i = 1; i < intervals.size(); i++) {
            if (end <= intervals[i][0]) {
                end = intervals[i][1];
                count++;
            }
        }
        return intervals.size() - count;
    }
};
// 划分字母区间
class lc763 {
public:
    vector<int> partitionLabels(string s) {
        vector<int> ans;
        int hash[27] = {0};                  // i为字符，hash[i]为字符出现的最后位置
        for (int i = 0; i < s.size(); i++) { // 统计每一个字符最后出现的位置
            hash[s[i] - 'a'] = i;
        }
        int right = 0;
        int left = 0;
        for (int i = 0; i < s.size(); i++) {
            right = max(hash[s[i] - 'a'], right);
            if (i == right) {
                ans.emplace_back(right - left + 1);
                left = right + 1;
            }
        }
        return ans;
    }
};
// 合并区间
class lc56 {
public:
    static bool cmp(vector<int> a, vector<int> b) { return a[0] < b[0]; }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;
        sort(intervals.begin(), intervals.end(), cmp);
        int left = intervals[0][0];
        int right = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= right)
                right = max(intervals[i][1], right);
            else {
                ans.emplace_back(vector<int>{left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        ans.emplace_back(vector<int>{left, right});
        return ans;
    }
    class Solution {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            vector<vector<int>> result;
            if (intervals.size() == 0) return result; // 区间集合为空直接返回
            // 排序的参数使用了lambda表达式
            sort(intervals.begin(), intervals.end(),
                 [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

            // 第一个区间就可以放进结果集里，后面如果重叠，在result上直接合并
            result.push_back(intervals[0]);

            for (int i = 1; i < intervals.size(); i++) {
                if (result.back()[1] >= intervals[i][0]) { // 发现重叠区间
                    // 合并区间，只更新右边界就好，因为result.back()的左边界一定是最小值，因为我们按照左边界排序的
                    result.back()[1] = max(result.back()[1], intervals[i][1]);
                }
                else {
                    result.push_back(intervals[i]); // 区间不重叠
                }
            }
            return result;
        }
    };
};
// 单调递增的数字
class lc738 {
public:
    int monotoneIncreasingDigits(int n) {
        string nums = to_string(n);
        int flag = nums.size() - 1;
        for (int i = nums.size() - 1; i >= 1; i--) {
            if (nums[i] < nums[i - 1]) {
                nums[i - 1]--;
                for (int j = i; j < nums.size(); j++) { nums[j] = '9'; }
            }
        }
        return stoi(nums);
    }
    // 上面是on2，可以改进啊
    class Solution {
    public:
        int monotoneIncreasingDigits(int N) {
            string strNum = to_string(N);
            // flag用来标记赋值9从哪里开始
            // 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
            int flag = strNum.size();
            for (int i = strNum.size() - 1; i > 0; i--) {
                if (strNum[i - 1] > strNum[i]) {
                    flag = i;
                    strNum[i - 1]--;
                }
            }
            for (int i = flag; i < strNum.size(); i++) { strNum[i] = '9'; }
            return stoi(strNum);
        }
    };
};

int main() { int n = 10; }