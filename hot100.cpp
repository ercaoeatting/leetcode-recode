#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution10 {
public:
    // o(m+n)
    double findMedianSortedArrays1(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) {
            swap(a, b); // 保证下面的 i 可以从 0 开始枚举
        }

        int m = a.size(), n = b.size();
        a.insert(a.begin(), INT_MIN); // 最左边插入 -∞
        b.insert(b.begin(), INT_MIN);
        a.push_back(INT_MAX); // 最右边插入 ∞
        b.push_back(INT_MAX);

        // 枚举 nums1 有 i 个数在第一组
        // 那么 nums2 有 (m + n + 1) / 2 - i 个数在第一组
        int i = 0, j = (m + n + 1) / 2;
        while (true) {
            if (a[i] <= b[j + 1] && a[i + 1] > b[j]) { // 写 >= 也可以 ////
                int max1 = max(a[i], b[j]);            // 第一组的最大值
                int min2 = min(a[i + 1], b[j + 1]);    // 第二组的最小值
                return (m + n) % 2 ? max1 : (max1 + min2) / 2.0;
            }
            i++;
            j--;
        }
    }
    double findMedianSortedArrays2(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) {
            swap(a, b); // 保证下面的 i 可以从 0 开始枚举
        }

        int m = a.size(), n = b.size();
        a.insert(a.begin(), INT_MIN); // 最左边插入 -∞
        b.insert(b.begin(), INT_MIN);
        a.push_back(INT_MAX); // 最右边插入 ∞
        b.push_back(INT_MAX);

        // a[i] <= b[j + 1] i越小越能成立，因此二分最大成立的i
        //  a[left] <= b[j + 1] a[right] > b[j+1]
        //  闭区间 [left,right]
        int left = 0, right = m;
        while (left <= right) {
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;
            if (a[i] <= b[j + 1]) {
                left = i + 1;
            } else {
                right = i - 1;
            }
        }
        int i = right;
        int j = (m + n + 1) / 2 - i;
        int max1 = max(a[i], b[j]);
        int min2 = min(a[i + 1], b[j + 1]);
        return (m + n) % 2 ? max1 : (max1 + min2) / 2.0;
    }
};
class Solution_10_good {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) {
            swap(a, b); // 确保 a 是较短的数组
        }

        int m = a.size(), n = b.size();
        int left = -1, right = m; // 左开右开区间 (left, right)

        while (left + 1 < right) { // 区间至少有两个元素时才继续
            int i = (left + right) / 2;      // 取中间点
            int j = (m + n + 1) / 2 - 2 - i; // 计算 j

            if (a[i] <= b[j + 1]) {
                left = i; // 缩小到 (i, right)
            } else {
                right = i; // 缩小到 (left, i)
            }
        }

        // 最终 left 是满足 a[left] <= b[j + 1] 的最大 i
        int i = left;
        int j = (m + n + 1) / 2 - 2 - i;

        // 处理边界情况
        int ai = (i >= 0) ? a[i] : INT_MIN;
        int bj = (j >= 0) ? b[j] : INT_MIN;
        int ai1 = (i + 1 < m) ? a[i + 1] : INT_MAX;
        int bj1 = (j + 1 < n) ? b[j + 1] : INT_MAX;

        // 计算中位数
        int max_left = max(ai, bj);
        int min_right = min(ai1, bj1);

        return (m + n) % 2 ? max_left : (max_left + min_right) / 2.0;
    }
};
class Solution_10_logmplusn {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        if (total % 2 == 0) {
            int left = findKth(nums1, 0, nums2, 0, total / 2);
            int right = findKth(nums1, 0, nums2, 0, total / 2 + 1);
            return (left + right) / 2.0;
        } else {
            return findKth(nums1, 0, nums2, 0, total / 2 + 1);
        }
    }

private:
    int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        // 确保nums1是较短的数组
        if (nums1.size() - i > nums2.size() - j) {
            return findKth(nums2, j, nums1, i, k);
        }
        // 边界情况1：nums1已经全部排除
        if (i == nums1.size()) {
            return nums2[j + k - 1];
        }
        // 边界情况2：只需要找第1小的数
        if (k == 1) {
            return min(nums1[i], nums2[j]);
        }

        // 取两个数组的第k/2个元素
        int si = min((int)nums1.size(), i + k / 2);
        int sj = j + k - k / 2;

        if (nums1[si - 1] < nums2[sj - 1]) {
            // nums1[0...si-2]不可能存在第k小的元素
            return findKth(nums1, si, nums2, j, k - (si - i));
        } else {
            return findKth(nums1, i, nums2, sj, k - (sj - j));
        }
    }
};
class Solution_mia {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        if (n > m) // 保证数组1一定最短
        {
            return findMedianSortedArrays(nums2, nums1);
        }

        // Ci
        // 为第i个数组的割,比如C1为2时表示第1个数组只有2个元素。LMaxi为第i个数组割后的左元素。RMini为第i个数组割后的右元素。
        int LMax1, LMax2, RMin1, RMin2, c1, c2,
            lo = 0, hi = 2 * n; // 我们目前是虚拟加了'#'所以数组1是2*n长度

        while (lo <= hi) // 二分
        {
            c1 = (lo + hi) / 2; // c1是二分的结果
            c2 = m + n - c1;

            LMax1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
            RMin1 = (c1 == 2 * n) ? INT_MAX : nums1[c1 / 2];
            LMax2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
            RMin2 = (c2 == 2 * m) ? INT_MAX : nums2[c2 / 2];

            if (LMax1 > RMin2)
                hi = c1 - 1;
            else if (LMax2 > RMin1)
                lo = c1 + 1;
            else
                break;
        }
        return (max(LMax1, LMax2) + min(RMin1, RMin2)) / 2.0;
    }
};
class Solution32 {
public:
    int longestValidParentheses(string s) {
        stack<pair<char, int>> st;
        vector<int> resp;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                st.push({s[i], i});
            else {
                if (st.empty())
                    continue;
                else {
                    resp.push_back(st.top().second);
                    resp.push_back(i);
                    st.pop();
                }
            }
        }
        ranges::sort(resp);
        int ans = 0, count = 1;
        for (int i = 1; i < resp.size(); i++) {
            if (resp[i] == resp[i - 1] + 1) {
                ans = max(++count, ans);
            } else {
                count = 1;
            }
        }
        return ans;
    }
};
