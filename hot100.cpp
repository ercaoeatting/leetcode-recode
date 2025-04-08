#include <algorithm>
#include <climits>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution10 {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
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
            } //////
            i++; // 继续枚举
            j--;
        }
    }
};

class Solution {
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
            if (resp[i] == resp[i - 1] + 1) { ans = max(++count, ans); }
            else { count = 1; }
        }
        return ans;
    }
};
int main() {
    string s = "()(()";
    Solution().longestValidParentheses(s);
}