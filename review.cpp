#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
ostream &operator<<(ostream &out, vector<vector<int>> &a) {
    for (auto a0 : a) {
        for (int x : a0) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return out;
}
class Solution707 {
public:
    int search(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (nums[middle] > target) {
                right = middle - 1;
            } else if (nums[middle] < target) {
                left = middle + 1;
            } else {
                return middle;
            }
        }
        return -1;
    }
};
//
class Solution27 {
public:
    int removeElement(vector<int> &nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
// 有序数组的平方
class Solution977 {
public:
    vector<int> sortedSquares(vector<int> &nums) {
        int size = nums.size();
        vector<int> result(nums.size(), 0);
        int left = 0, right = nums.size() - 1;
        int k = right;
        while (left <= right) {
            if (nums[left] * nums[left] < nums[right] * nums[right]) {
                result[k--] = nums[right] * nums[right];
                right--;
            } else {
                result[k--] = nums[left] * nums[left];
                left++;
            }
        }
        return result;
    }
};
// 长度最小的子数组
class Solution209 {
public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int i = 0, j = 0, sum = 0;
        int result = INT32_MAX;
        while (j < nums.size()) {
            sum += nums[j];
            while (sum >= target) {
                result = min(result, j - i + 1);
                sum -= nums[i++];
            }
            j++;
        }
        return result == INT32_MAX ? 0 : result;
    }
};
// 水果篮子
class Solution904 {
public:
    int totalFruit(vector<int> &fruits) {
        int i = 0, j = 0, result = 0;
        unordered_map<int, int> type;
        while (j < fruits.size()) {
            type[fruits[j]]++;

            while (type.size() > 2) {
                type[fruits[i]]--;
                if (type[fruits[i]] == 0) type.erase(fruits[i]);
                i++;
            }
            result = max(result, (j++) - i + 1);
        }
        return result;
    }
};

// 螺旋矩阵2
class Solution59 {
public:
    vector<vector<int>> generateMatrix(int n) {
        int left = 0, top = 0, right = n - 1, bottom = n - 1, m = 1;
        vector<vector<int>> res(n, vector<int>(n, 0));
        while (left <= right && top <= bottom) {
            for (int i = left; i <= right; i++) {
                res[top][i] = m++;
            }
            top++;
            for (int j = top; j <= bottom; j++) {
                res[j][right] = m++;
            }
            right--;
            for (int k = right; k >= left; k--) {
                res[bottom][k] = m++;
            }
            bottom--;
            for (int x = bottom; x >= top; x--) {
                res[x][left] = m++;
            }
            left++;
        }
        return res;
    }
};

// 单链表
struct ListNode {
    int val;                                // 节点上存储的元素
    ListNode *next;                         // 指向下一个节点的指针
    ListNode(int x) : val(x), next(NULL) {} // 节点的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution203 {
public:
    ListNode *removeElements(ListNode *head, int val) {
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode *cur = dummyHead;
        while (cur->next) {
            if (cur->next->val == val) {
                ListNode *tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummyHead->next;
        delete dummyHead;
        return head;
    }
};

class MyLinkedList {
public:
    struct node {
        int val;
        node *next;
        node(int val) : val(val), next(nullptr) {}
        node(int val, node *next) : val(val), next(next) {}
    };
    MyLinkedList() {
        _dummyHead = new node(0);
        _size = 0;
    }

    int get(int index) {
        if (index < 0 || index > (_size - 1)) {
            return -1;
        }
        node *tmp = _dummyHead->next;
        while (index--) {
            tmp = tmp->next;
        }
        return tmp->val;
    }

    void addAtHead(int val) {
        node *tmp = new node(val);
        if (_dummyHead->next) tmp->next = _dummyHead->next;
        _dummyHead->next = tmp;
        _size++;
        return;
    }

    void addAtTail(int val) {
        node *newNode = new node(val);
        node *cur = _dummyHead;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
        _size++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0) index = 0;
        if (index > (_size)) {
            return;
        }
        node *cur = _dummyHead;
        while (index--) {
            cur = cur->next;
        }
        node *tmp = new node(val, cur->next);
        cur->next = tmp;
        _size++;
        return;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index > (_size - 1)) return;
        node *cur = _dummyHead;
        while (index--) {
            cur = cur->next;
        }
        node *tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        _size--;
        return;
    }

private:
    int _size;
    node *_dummyHead;
};

class Solution206 {
public:
    ListNode *reverseList1(ListNode *head) {
        if (!head->next) return head;
        ListNode *pre = nullptr;
        ListNode *cur = head;
        while (cur) {
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
    ListNode *reverse(ListNode *pre, ListNode *cur) {
        if (!cur) return pre;
        ListNode *tmp = cur->next;
        cur->next = pre;
        return reverse(cur, tmp);
    }
    ListNode *reverseList(ListNode *head) { return reverse(nullptr, head); }
};

class Solution24 {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode *cur = dummyHead;
        while (cur->next && cur->next->next) {
            ListNode *tmp = cur->next;
            ListNode *tmp2 = cur->next->next;
            cur->next = cur->next->next;
            tmp->next = tmp2->next;
            tmp2->next = tmp;
            cur = tmp;
        }
        return dummyHead->next;
    }
};

class Solution19 {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *dummyHead = new ListNode(0, head);
        dummyHead->next = head;
        ListNode *fast = dummyHead, *slow = dummyHead;
        while (n--) {
            fast = fast->next;
        }
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *cur = slow->next;
        slow->next = slow->next->next;
        delete cur;
        return head;
    }
};

// 字母异位词
class Solution242 {
public:
    bool isAnagram(string s, string t) {
        int a[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            a[s[i] - 'a']++;
        }
        for (int i = 0; i < s.size(); i++) {
            a[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (a[i] != 0) return false;
        }
        return true;
    }
};
// 面试题链表相交
class Solution_meet {
public:
    int len(ListNode *head) {
        ListNode *cur = head;
        int len = 0;
        while (cur) {
            cur = cur->next;
            len++;
        }
        return len;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = len(headA);
        int lenB = len(headB);
        ListNode *curA = headA, *curB = headB;
        if (lenA < lenB) {
            swap(curA, curB);
        }
        int dlen = abs(lenA - lenB);
        while (dlen--) {
            curA = curA->next;
        }
        while (curA) {
            if (curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return nullptr;
    }
};
// 链表环
class Solution142 {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow) {
                ListNode *findRes = head, *help = fast;
                while (findRes != help) {
                    findRes = findRes->next;
                    help = help->next;
                }
                return findRes;
            }
        }
        return nullptr;
    }
};
// 两个数组的交集
class Solution349 {
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        unordered_set<int> inter;
        unordered_set<int> res;
        inter.insert(nums1.begin(), nums1.end());
        for (int num : nums2) {
            if (inter.find(num) != inter.end()) {
                res.insert(num);
            }
        }
        return vector<int>(res.begin(), res.end());
    }
};
// 快乐数
class Solution202 {
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
        unordered_set<int> sums;
        int sum = n;
        while (1) {
            sum = getSum(sum);
            if (sum == 1) return true;
            if (sums.find(sum) != sums.end()) return false;
            sums.insert(sum);
        }
    }
};

class Solution1 {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            auto iter = map.find(target - nums[i]);
            if (iter != map.end())
                return {iter->second, i};
            else
                map.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};
// 四数相加II
class Solution454 {
public:
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4) {
        unordered_map<int, int> umap;
        int count = 0;
        for (int a : nums1) {
            for (int b : nums2) {
                umap[a + b]++;
            }
        }

        for (int c : nums3) {
            for (int d : nums4) {
                if (umap.find(-(c + d)) != umap.end()) {
                    count += umap[-(c + d)];
                }
            }
        }
        return count;
    }
};
// 赎金信
class Solution383 {
public:
    bool canConstruct1(string ransomNote, string magazine) {
        unordered_map<char, int> umap;
        for (char i : magazine) {
            umap[i]++;
        }
        for (char j : ransomNote) {
            if (umap.find(j) == umap.end()) {
                return false;
            } else {
                umap[j]--;
                if (umap[j] < 0) return false;
            }
        }
        return true;
    }
    // 用数组其实就行
    bool canConstruct(string ransomNote, string magazine) {
        int record[26] = {0};
        for (char i : magazine) {
            record[i - 'a']++;
        }
        for (char j : ransomNote) {
            if (record[j - 'a'] > 0) {
                record[j - 'a']--;
                continue;
            }
            return false;
        }
        return true;
    }
};
// 三数之和
class Solution15 {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> result(0);
        if (nums.size() <= 2) return result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) return result;
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    right--;
                    left++;
                }
            }
        }
        return result;
    }
};

class Solution18 {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> result(0);
        if (nums.size() <= 3) return result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (i == (nums.size() - 3)) return result;
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] > target && nums[i] + nums[j] > 0) break;
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int left = j + 1, right = nums.size() - 1;
                while (left < right) {
                    if ((long)(nums[i] + nums[j] + nums[left] + nums[right] < target))
                        left++;
                    else if ((long)nums[i] + nums[j] + nums[left] + nums[right] > target)
                        right--;
                    else {
                        result.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    }
                }
            }
        }
        return result;
    }
};

// 541 反串字符串
class Solution541 {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2 * k) {
            if (i + k <= s.size())
                reverse(s.begin() + i, s.begin() + i + k);
            else
                reverse(s.begin() + i, s.end());
        }
        return s;
    }
};
// 151 反转字符串里单词
class Solution151 {
public:
    void deleteSpace(string &s) {
        int slow = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                if (slow != 0) s[slow++] = ' ';
                while (i < s.size() && s[i] != ' ') s[slow++] = s[i++];
            }
        }
        s.resize(slow);
    }
    void reverseS(string &s, int a, int b) {
        for (int i = a, j = b; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
    string reverseWords(string s) {
        deleteSpace(s);
        reverseS(s, 0, s.size() - 1);
        int a = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                int b = i - 1;
                reverseS(s, a, b);
                a = i + 1;
            }
            if (i == s.size() - 1) {
                reverseS(s, a, i);
            }
        }
        return s;
    }
};
// 459.重复的子字符串
//
// KMP 28
class Solution28 {
    void getNext(int *next, const string &s) {
        int j = 0;
        next[0] = 0;
        for (int i = 1; i < s.size(); i++) {
            while (j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            } // 前后缀不同
            if (s[i] == s[j]) {
                j++;
            } // 找到相同的前后缀
            next[i] = j;
        }
    }

public:
    int strStr(string haystack, string needle) {
        if (needle.size() == 0) return 0;
        int next[needle.size()];
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }
            if (j == needle.size()) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};

// 栈和队列
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// 232 用栈实现队列
class MyQueue {
private:
    stack<int> in;
    stack<int> out;

public:
    MyQueue() {}

    void push(int x) { in.push(x); }

    int pop() {
        if (!out.empty()) {
            int res = out.top();
            out.pop();
            return res;
        }
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
        int res = out.top();
        out.pop();
        return res;
    }

    int peek() {
        if (!out.empty()) {
            return out.top();
        }
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
        return out.top();
    }

    bool empty() { return in.empty() && out.empty(); }
};
// 225 用队列实现栈
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
class MyStack {
public:
    queue<int> que1, que2;
    MyStack() {}

    void push(int x) { que1.push(x); }

    int pop() {
        int size = que1.size();
        while (size-- && size >= 1) {
            que2.push(que1.front());
            que1.pop();
        }
        int res = que1.front();
        que1.pop();
        que1 = que2;            // 再将que2赋值给que1
        while (!que2.empty()) { // 清空que2
            que2.pop();
        }
        return res;
    }

    int top() {
        int size = que1.size() - 1;
        while (size--) {
            que2.push(que1.front());
            que1.pop();
        }
        int res = que1.front();
        que1 = que2;
        que1.push(res);
        while (!que2.empty()) { // 清空que2
            que2.pop();
        }
        return res;
    }

    bool empty() { return que1.empty() && que2.empty(); }
};
// 20 有效的括号
class Solution20 {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (!st.empty() && st.top() == c) {
                st.pop();
            } else if (c == '(')
                st.push(')');
            else if (c == '[')
                st.push(']');
            else if (c == '{')
                st.push('}');
            else
                return false;
        }
        return st.empty();
    }
};

// 1047 删除相邻项
class Solution1047 {
public:
    string removeDuplicates(string s) {
        stack<int> st;
        for (char c : s) {
            if (st.empty()) {
                st.push(c);
                continue;
            }
            if (st.top() == c)
                st.pop();
            else
                st.push(c);
        }
        string result = "";
        while (!st.empty()) { // 将栈中元素放到result字符串汇总
            result += st.top();
            st.pop();
        }
        reverse(result.begin(), result.end()); // 此时字符串需要反转一下
        return result;
    }
};
// 逆波兰表达式
class Solution150 {
public:
    int evalRPN(vector<string> &tokens) {
        stack<long long> st;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                long long num1 = st.top();
                st.pop();
                long long num2 = st.top();
                st.pop();
                if (tokens[i] == "+") st.push(num2 + num1);
                if (tokens[i] == "-") st.push(num2 - num1);
                if (tokens[i] == "*") st.push(num2 * num1);
                if (tokens[i] == "/") st.push(num2 / num1);
            } else {
                st.push(stoll(tokens[i]));
            }
        }

        int result = st.top();
        st.pop(); // 把栈里最后一个元素弹出（其实不弹出也没事）
        return result;
    }
};
// 239 滑动窗口最大值 难题
class Solution239 {
public:
    struct mostQ {
        deque<int> Q;
        void push(int c) {
            while (!Q.empty() && c > Q.back()) {
                Q.pop_back();
            }
            Q.push_back(c);
        }
        void pop(int c) {
            if (!Q.empty() && c == Q.front()) // 我感觉这里才是精华，能知道要不要弹出
                Q.pop_front();
        }
        int front() { return Q.front(); }
    };
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        mostQ mq;
        vector<int> res(nums.size() - k + 1, 0);
        for (int i = 0; i < k; i++) {
            mq.push(nums[i]);
        }
        res[0] = mq.front();
        int j = 1;
        for (int i = k; i < nums.size(); i++) {
            mq.pop(nums[i - k]);
            mq.push(nums[i]);
            res[j++] = mq.front();
        }
        return res;
    }
};
// 347 前k个高频元素
class Solution347 {
public:
    bool com(const pair<int, int> &lhs, const pair<int, int> &rhs) {
        return lhs.second > rhs.second; // Sort in descending order by frequency
    }

    vector<int> topKFrequent1(vector<int> &nums,
                              int k) { // 十足的笨办法  复杂度nlogn
        unordered_map<int, int> map;
        for (int num : nums) {
            map[num]++;
        }
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(),
             [](const pair<int, int> &lhs, const pair<int, int> &rhs) { return lhs.second > rhs.second; });
        vector<int> a(k);
        for (int i = 0; i < k; ++i) {
            a[i] = vec[i].first;
        }
        return a;
    }
    // 小顶堆

    // vector<int> topKFrequent(vector<int> &nums, int k) { // 复杂度nlogk
    //     // 要统计元素出现频率
    //     unordered_map<int, int> map; // map<nums[i],对应出现的次数>
    //     for (int i = 0; i < nums.size(); i++) { map[nums[i]]++; }

    //     // 对频率排序
    //     // 定义一个小顶堆，大小为k
    //     priority_queue<pair<int, int>, vector<pair<int, int>>,
    //     std::greater<int>> pri_que;

    //     // 用固定大小为k的小顶堆，扫面所有频率的数值
    //     for (unordered_map<int, int>::iterator it = map.begin(); it !=
    //     map.end(); it++) {
    //         pri_que.push(*it);
    //         if (pri_que.size() > k) { //
    //         如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
    //             pri_que.pop();
    //         }
    //     }

    //     //
    //     找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
    //     vector<int> result(k);
    //     for (int i = k - 1; i >= 0; i--) {
    //         result[i] = pri_que.top().first;
    //         pri_que.pop();
    //     }
    //     return result;
    // }
};
// 二叉树
//  144 前序
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution_preordrer {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> a;
        stack<TreeNode *> st;
        if (root == nullptr) return a;
        st.push(root);
        while (!st.empty()) {
            TreeNode *node = st.top();
            a.push_back(node->val);
            st.pop();
            st.push(node->right);
            st.push(node->left);
        }
        return a;
    }
};
// 迭代
class SolutionINORDER {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> a;
        stack<TreeNode *> st;
        if (root == nullptr) return a;
        TreeNode *cur = root;
        while (cur != nullptr || !st.empty()) {
            if (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            } else {
                cur = st.top();
                st.pop();
                a.push_back(cur->val);
                cur = cur->right;
            }
        }
        return a;
    }
};
// 226 INVERT
class Solution226 {
public:
    void prec(TreeNode *cur) {
        if (cur == nullptr) return;
        prec(cur->left);
        prec(cur->right);
        swap(cur->left, cur->right);
    }
    TreeNode *invertTree(TreeNode *root) {
        if (root == nullptr) return nullptr;
        prec(root);
        return root;
    }
};
// 层序遍历102
class Solution102 {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        queue<TreeNode *> q;
        vector<vector<int>> res;
        if (!root) return vector<vector<int>>();
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> tmp;
            while (size--) {
                TreeNode *cur = q.front();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                q.pop();
                tmp.push_back(cur->val);
            }
            res.push_back(tmp);
        }
        return res;
    }
};
// 199 二叉树的右视图
class Solution199 {
public:
    vector<int> rightSideView(TreeNode *root) {
        queue<TreeNode *> q;
        vector<int> res;
        if (!root) return vector<int>();
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            TreeNode *cur;
            while (size--) {
                cur = q.front();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                if (size == 0) res.push_back(cur->val);
                q.pop();
            }
        }
        return res;
    }
};
// 637. 二叉树的层平均值
class Solution637 {
public:
    vector<double> averageOfLevels(TreeNode *root) {
        queue<TreeNode *> q;
        vector<double> res;
        if (!root) return vector<double>();
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            double ave = 0;
            int whsize = size;
            TreeNode *cur;
            while (size--) {
                cur = q.front();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                q.pop();
                ave += (double)cur->val;
            }
            res.push_back(ave / whsize);
        }
        return res;
    }
};
// 116. 填充每个节点的下一个右侧节点指针
class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node *_left, Node *_right, Node *_next) : val(_val), left(_left), right(_right), next(_next) {}
};
class Solution116 {
public:
    Node *connect(Node *root) {
        queue<Node *> q;
        if (!root) return nullptr;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            Node *cur;
            while (size--) {
                cur = q.front();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                q.pop();
                if (size != 0)
                    cur->next = q.front();
                else
                    cur->next = nullptr;
            }
        }
        return root;
    }
};
// 104. 二叉树的最大深度

class Solution104 {
public:
    int maxDepth(TreeNode *root) {
        queue<TreeNode *> q;
        if (!root) return 0;
        q.push(root);
        int maxdep = 0;
        while (!q.empty()) {
            int size = q.size();
            TreeNode *cur;
            maxdep++;
            while (size--) {
                cur = q.front();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                q.pop();
            }
        }
        return maxdep;
    }
};
// 111. 二叉树的最小深度
class Solution111 {
public:
    int minDepth(TreeNode *root) {
        queue<TreeNode *> q;
        if (!root) return 0;
        q.push(root);
        int maxdep = 0;
        while (!q.empty()) {
            int size = q.size();
            TreeNode *cur;
            while (size--) {
                cur = q.front();
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                if (cur->left && cur->right) maxdep++;
                q.pop();
            }
        }
        return maxdep;
    }
};
// 101 对称二叉树
class Solution101 {
public:
    bool compare(TreeNode *left, TreeNode *right) {
        if (!left && !right)
            return true;
        else if ((left && !right) || (!left && right))
            return false;
        else if (left->val != right->val)
            return false;
        return compare(left->left, right->right) && compare(left->right, right->left);
    }
    bool isSymmetric(TreeNode *root) { return compare(root->left, root->right); }
};
// 222. 完全二叉树的节点个数
class Solution222 {
public:
    void getNum(TreeNode *cur, int &num) {
        if (cur == nullptr) return;
        getNum(cur->right, num);
        num++;
        getNum(cur->left, num);
    }
    int countNodes1(TreeNode *root) {
        int num = 0;
        getNum(root, num);
        return num;
    }
    int countNodes(TreeNode *root) {
        if (!root) return 0;
        TreeNode *left = root->left;
        TreeNode *right = root->right;
        int leftDepth = 0,
            rightDepth = 0; // 这里初始为0是有目的的，为了下面求指数方便
        while (left) {
            left = left->left;
            leftDepth++;
        }
        while (right) {
            right = right->right;
            rightDepth++;
        }
        if (leftDepth == rightDepth) {
            return (2 << leftDepth) - 1; // 注意(2<<1) 相当于2^2，所以leftDepth初始为0
        }
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};
// 110 平衡二叉树
class Solution110 {
public:
    int balance(TreeNode *root) {
        if (root == nullptr) return 0;
        int lh = balance(root->left);
        if (lh == -1) return -1;
        int rh = balance(root->right);
        if (rh == -1) return -1;
        int zh = abs(lh - rh);
        if (zh > 1)
            return -1;
        else
            return 1 + max(lh, rh);
    }
    bool isBalanced(TreeNode *root) { return balance(root); }
};

// 257 二叉树的所有路径
class Solution257 {
public:
    void getWay(TreeNode *cur, vector<string> &way, vector<int> &s) {
        s.push_back(cur->val);
        if (cur->left == NULL && cur->right == NULL) {
            string path;
            for (int ss : s) {
                path += to_string(ss);
                path += "->";
            }
            path.pop_back();
            path.pop_back();
            way.push_back(path);
        }
        if (cur->left) {
            getWay(cur->left, way, s);
            s.pop_back();
        }
        if (cur->right) {
            getWay(cur->right, way, s);
            s.pop_back();
        }
    }
    vector<string> binaryTreePaths(TreeNode *root) {
        // 中左右
        vector<int> s;
        vector<string> res;
        getWay(root, res, s);
        return res;
    }
};
// 513. 找树左下角的值
class Solution513 {
public:
    int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        int res;
        while (!q.empty()) {
            int size = q.size();
            int sizet = size;
            while (size--) {
                TreeNode *cur = q.front();
                if (sizet == size + 1) res = cur->val;
                q.pop();
                if (cur->left) {
                    q.push(cur->left);
                }
                if (cur->right) {
                    q.push(cur->right);
                }
            }
        }
        return res;
    }
};
// 112 路径综合
class Solution112 {
public:
    bool res1 = false, res2 = false;
    bool hasPathSum(TreeNode *root, int targetSum) {
        if (root == nullptr) return false;
        if (root->val == targetSum && !root->left && root->right) return true;
        if (root->left) {
            res1 = hasPathSum(root->left, targetSum - root->val);
        }
        if (root->right) {
            res2 = hasPathSum(root->right, targetSum - root->val);
        }
        return res1 || res2;
    }
    bool hasPathSum2(TreeNode *root, int targetSum) {
        stack<pair<TreeNode *, int>> st;
        if (!root) return false;
        st.push({root, targetSum});
        while (!st.empty()) {
            pair<TreeNode *, int> pcur = st.top();
            st.pop();
            if (pcur.first->val == pcur.second && !pcur.first->left && !pcur.first->right) return true;
            if (pcur.first->left) {
                st.push({pcur.first->left, pcur.second - pcur.first->val});
            }
            if (pcur.first->right) {
                st.push({pcur.first->right, pcur.second - pcur.first->val});
            }
        }
        return false;
    }
};

// 106. 从中序与后序遍历序列构造二叉树
class Solution106 {
public:
    class Solution {
    private:
        // 中序区间：[inorderBegin, inorderEnd)，后序区间[postorderBegin,
        // postorderEnd)
        TreeNode *traversal(vector<int> &inorder, int inorderBegin, int inorderEnd, vector<int> &postorder,
                            int postorderBegin, int postorderEnd) {
            if (postorderBegin == postorderEnd) return NULL;

            int rootValue = postorder[postorderEnd - 1];
            TreeNode *root = new TreeNode(rootValue);

            if (postorderEnd - postorderBegin == 1) return root;

            int delimiterIndex;
            for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++) {
                if (inorder[delimiterIndex] == rootValue) break;
            }
            // 切割中序数组
            // 左中序区间，左闭右开[leftInorderBegin, leftInorderEnd)
            int leftInorderBegin = inorderBegin;
            int leftInorderEnd = delimiterIndex;
            // 右中序区间，左闭右开[rightInorderBegin, rightInorderEnd)
            int rightInorderBegin = delimiterIndex + 1;
            int rightInorderEnd = inorderEnd;

            // 切割后序数组
            // 左后序区间，左闭右开[leftPostorderBegin, leftPostorderEnd)
            int leftPostorderBegin = postorderBegin;
            int leftPostorderEnd =
                postorderBegin + delimiterIndex - inorderBegin; // 终止位置是 需要加上 中序区间的大小size
            // 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
            int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);
            int rightPostorderEnd = postorderEnd - 1; // 排除最后一个元素，已经作为节点了

            root->left =
                traversal(inorder, leftInorderBegin, leftInorderEnd, postorder, leftPostorderBegin, leftPostorderEnd);
            root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, postorder, rightPostorderBegin,
                                    rightPostorderEnd);

            return root;
        }

    public:
        TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
            if (inorder.size() == 0 || postorder.size() == 0) return NULL;
            // 左闭右开的原则
            return traversal(inorder, 0, inorder.size(), postorder, 0, postorder.size());
        }
    };
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (inorder.size() == 0) return nullptr;
        int rootval = postorder[postorder.size() - 1];
        TreeNode *root = new TreeNode(rootval);
        if (inorder.size() == 1) return root;
        int split = -1;
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i] == rootval) {
                split = i;
            }
        }
        vector<int> leftTreein(inorder.begin(), inorder.begin() + split);
        vector<int> leftTreepo(postorder.begin(), postorder.begin() + leftTreein.size());
        vector<int> rightTreein(inorder.begin() + split + 1, inorder.end());
        vector<int> rightTreepo(postorder.begin() + leftTreein.size(), postorder.end() - 1);
        root->left = buildTree(leftTreein, leftTreepo);
        root->right = buildTree(rightTreein, rightTreepo);
        return root;
    }
};
// 654 最大二叉树
class Solution654 {
public:
    TreeNode *traversal(vector<int> &nums, int begin, int end) {
        int size = end - begin;
        if (size == 0) return nullptr;
        int maxnum = INT32_MIN;
        int maxpos = begin;
        for (int i = begin; i < end; i++) {
            if (nums[i] > maxnum) {
                maxpos = i;
                maxnum = nums[i];
            }
        }
        TreeNode *root = new TreeNode(maxnum);
        if (size == 1) return root;
        root->left = traversal(nums, begin, maxpos);
        root->right = traversal(nums, maxpos + 1, end);
        return root;
    }
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) { return traversal(nums, 0, nums.size()); }
};
// 617 合并二叉树
class Solution617 {
public:
    // 写的不怎么样
    TreeNode *traversal(TreeNode *root1, TreeNode *root2) {
        if (!root1 && !root2) return nullptr; // 两棵树都为空，返回空
        // 如果 root1 或 root2 为空，则取另一个树的值，否则相加
        int val1 = (root1 ? root1->val : 0);
        int val2 = (root2 ? root2->val : 0);
        TreeNode *root = new TreeNode(val1 + val2);
        // 递归合并左右子树
        if (root1 || root2) {
            root->left = traversal(root1 ? root1->left : nullptr, root2 ? root2->left : nullptr);
            root->right = traversal(root1 ? root1->right : nullptr, root2 ? root2->right : nullptr);
        }
        return root;
    }
    // 这段好点
    TreeNode *mergeTrees2(TreeNode *t1, TreeNode *t2) {
        if (t1 == NULL) return t2;                     // 如果t1为空，合并之后就应该是t2
        if (t2 == NULL) return t1;                     // 如果t2为空，合并之后就应该是t1
        t1->val += t2->val;                            // 中
        t1->left = mergeTrees2(t1->left, t2->left);    // 左
        t1->right = mergeTrees2(t1->right, t2->right); // 右
        return t1;
    }
};

// 700. 二叉搜索树中的搜索
class Solution700 {
public:
    TreeNode *searchBST1(TreeNode *root, int val) {
        if (!root) return nullptr;
        if (root->val == val)
            return root;
        else if (root->val > val)
            return searchBST1(root->left, val);
        else
            return searchBST1(root->right, val);
    }
    TreeNode *searchBST(TreeNode *root, int val) {
        if (!root) return nullptr;
        while (root) {
            if (root->val == val)
                return root;
            else if (root->val > val)
                root = root->left;
            else
                root = root->right;
        }
        return nullptr;
    }
};
// 530.二叉搜索树的最小绝对差
class Solution530 {
public:
    int delta = INT_MAX;
    TreeNode *pre = nullptr;
    void travel(TreeNode *cur) {
        if (!cur) return;
        travel(cur->left);
        if (pre) {
            delta = min(delta, cur->val - pre->val);
        }
        pre = cur;
        travel(cur->right);
    }
    int getMinimumDifference2(TreeNode *root) {
        travel(root);
        return delta;
    }
    int getMinimumDifference(TreeNode *root) {
        stack<TreeNode *> st;
        if (root) st.push(root);
        while (!st.empty()) {
            TreeNode *cur = st.top();
            if (!cur) {
                st.pop();
                if (cur->left) st.push(cur->left);
                st.push(cur);
                st.push(nullptr);
                if (cur->right) st.push(cur->right);
            } else {
                st.pop();
                cur = st.top();
                st.pop();
                if (pre) {
                    delta = min(delta, cur->val - pre->val);
                }
                pre = cur;
            }
        }
        return delta;
    }
};
// 98. 验证二叉搜索树
class Solution98 {
public:
    int maxval = INT_MIN;
    void travel(TreeNode *cur, vector<int> &s) {
        if (cur == nullptr) return;
        travel(cur->left, s);
        s.push_back(cur->val);
        travel(cur->right, s);
    }
    bool isValidBST(TreeNode *cur) {
        if (!cur) return true;
        bool reslef = isValidBST(cur);
        if (cur->val > maxval)
            maxval = cur->val;
        else
            return false;
        bool resrig = isValidBST(cur);
        return reslef && resrig;
    }
    bool isValidBST2(TreeNode *root) {
        vector<int> s;
        travel(root, s);
        for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] >= s[i + 1]) return false;
        }
        return true;
    }
};
// 501.二叉搜索树中的众数
class Solution501_1 {
public:
    unordered_map<int, int> umap;
    void travel(TreeNode *cur) {
        if (!cur) return;
        travel(cur->left);
        umap[cur->val]++;
        travel(cur->right);
    }

    vector<int> findMode1(TreeNode *root) {
        travel(root);
        vector<pair<int, int>> res1(umap.begin(), umap.end());
        sort(res1.begin(), res1.end(),
             [&](const pair<int, int> &a, const pair<int, int> &b) { return a.second > b.second; });
        vector<int> res;
        res.push_back(res1[0].first);
        for (int i = 1; i < res1.size(); i++) {
            if (res1[i].second == res1[0].second) res.push_back(res1[i].first);
        }
        return res;
    }
};
class Solution501_2 {
public:
    int maxf = 0;
    int f = 0;
    vector<int> res;
    TreeNode *pre = nullptr;
    void traversal(TreeNode *root) {
        if (root == nullptr) return;
        traversal(root->left);
        // 中
        // 先处理f
        if (!pre) {
            f = 1;
        } // 第一个非空节点
        else if (root->val == pre->val) {
            f++;
        } else { // 3 3 4（遇到了这个节点） 4
            f = 1;
        }
        // 再处理具体的众数
        if (f > maxf) {
            maxf = f;
            res.clear();
            res.push_back(root->val);
        } else if (f == maxf) {
            res.push_back(root->val);
        }
        pre = root;
        traversal(root->right);
    }
    vector<int> findMode(TreeNode *root) {
        traversal(root);
        return res;
    }
};

// 236. 二叉树的最近公共祖先
class Solution236 {
public:
    TreeNode *travel(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (!root || root == p || root == q) return root;
        TreeNode *cur = travel(root->left, p, q);
        TreeNode *cur2 = travel(root->right, p, q);
        if (cur && cur2)
            return root;
        else if (!cur2)
            return cur;
        else if (!cur)
            return cur2;
        return nullptr;
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) { return travel(root, p, q); }
};
// 701 二叉搜索树的插入
class Solution701 {
public:
    TreeNode *insertIntoBST(TreeNode *root, int val) {
        if (!root) return new TreeNode(val);
        if (root->val > val)
            root->left = insertIntoBST(root->left, val);
        else
            root->right = insertIntoBST(root->right, val);
        return root;
    }
};
// 450 二叉搜索树的删除
class Solution450 {
public:
    TreeNode *deleteNode(TreeNode *root, int key) {
        if (root == nullptr) return nullptr;
        if (root->left) root->left = deleteNode(root->left, key);
        if (root->right) root->right = deleteNode(root->right, key);
        if (root->val == key) {
            // 左右孩子都空
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            }
            // 左或者右孩子不空
            else if (root->left && !root->right) {
                return root->left;
            } else if (!root->left && root->right) {
                return root->right;
            }
            // 左右都不空
            else {
                TreeNode *rootLeft = root->left;
                TreeNode *rootRight = root->right;
                root = root->right;
                while (root->left) {
                    root = root->left;
                }
                root->left = rootLeft;
                return rootRight;
            }
        }
        return root;
    }
};
// 669. 修剪二叉搜索树
class Solution669 {
public:
    TreeNode *trimBST(TreeNode *root, int low, int high) {
        if (!root) return nullptr;
        if (root->left) root->left = trimBST(root->left, low, high);
        if (root->right) root->right = trimBST(root->right, low, high);
        if (root->val < low)
            return root->right;
        else if (root->val > high)
            return root->left;
        else
            return root;
        return root;
    }
};
// 654.最大二叉树
class Solution654_2 {
public:
    TreeNode *travel(vector<int> &nums, int left, int right) {
        if (left > right) return nullptr;
        int max_size = -1, max_value = INT_MIN;
        for (int i = left; i <= right; i++) {
            if (nums[i] > max_value) {
                max_size = i;
                max_value = nums[i];
            }
        }
        TreeNode *root = new TreeNode(max_value);
        root->left = travel(nums, left, max_size - 1);
        root->right = travel(nums, max_size + 1, right);
        return root;
    }
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) { return travel(nums, 0, nums.size() - 1); }
};
// 108. 将有序数组转换为二叉搜索树
class Solution108 {
public:
    TreeNode *travelsal(vector<int> &nums, int left, int right) {
        if (left > right) return nullptr;
        int max_value = nums[(left + right) / 2];
        int max_size = (left + right) / 2;
        TreeNode *root = new TreeNode(max_value);
        root->left = travelsal(nums, left, max_size - 1);
        root->right = travelsal(nums, max_size + 1, right);
        return root;
    }
    TreeNode *sortedArrayToBST(vector<int> &nums) { return travelsal(nums, 0, nums.size() - 1); }
};
// 538. 把二叉搜索树转换为累加树
class Solution538 {
public:
    TreeNode *pre = nullptr;
    TreeNode *convertBST(TreeNode *root) {
        if (!root) return nullptr;
        if (root->right) convertBST(root->right);
        if (pre) {
            root->val += pre->val;
        }
        pre = root;
        if (root->left) convertBST(root->left);
        return root;
    }
};

// 回溯
// 77. 组合
class Solution77 {
    vector<vector<int>> res;
    vector<int> path;
    void back(int n, int k, int start) {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }
        for (int i = start; i <= n /*  n - k + path.size() + 1  */; i++) {
            path.push_back(i);
            back(n, k, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        back(n, k, 1);
        return res;
    }
};
// 216. 组合总和 III
class Solution216 {
    vector<vector<int>> res;
    vector<int> path;
    void back(int k, int n, int start, int sum_now) {
        if (path.size() == k) {
            if (sum_now == n) res.push_back(path);
            return;
        }
        for (int i = start; i <= 9; i++) {
            path.push_back(i);
            back(k, n, i + 1, sum_now + i);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        back(k, n, 1, 0);
        return res;
    }
};
// 17. 电话号码的字母组合
class Solution17 {
    const string letterMap[10] = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz", // 9
    };

public:
    vector<string> result;
    void getCombinations(const string &digits, int index,
                         const string &s) { // 注意参数的不同
        if (index == digits.size()) {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0';
        string letters = letterMap[digit];
        for (int i = 0; i < letters.size(); i++) {
            getCombinations(digits, index + 1,
                            s + letters[i]); // 注意这里的不同
        }
    }
    vector<string> letterCombinations(string digits) {
        result.clear();
        if (digits.size() == 0) {
            return result;
        }
        getCombinations(digits, 0, "");
        return result;
    }
};
// 39. 组合总和
class Solution39 {
public:
    vector<vector<int>> res;
    vector<int> path;
    void back(vector<int> &candidates, int target, int sum, int start) {
        if (sum > target) return;
        if (sum == target) {
            res.push_back(path);
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            path.push_back(candidates[i]);
            back(candidates, target, sum + candidates[i], i);
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        back(candidates, target, 0, 0);
        return res;
    }
};
// 40. 组合总和 II
class Solution40 {
public:
    vector<vector<int>> res;
    vector<int> path;
    void back(vector<int> &candidates, int target, int sum, int start, vector<bool> used) {
        if (sum > target) return;
        if (sum == target) {
            res.push_back(path);
            return;
        }
        // if (i > start && candidates[i] == candidates[i - 1]) continue;
        for (int i = start; i < candidates.size() && sum + candidates[i] <= target; i++) {
            if (i > 0 && used[i - 1] == 0 && candidates[i] == candidates[i - 1]) continue;
            path.push_back(candidates[i]);
            used[i] = 1;
            back(candidates, target, sum + candidates[i], i + 1, used);
            used[i] = 0;
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<bool> used(candidates.size(), 0);
        back(candidates, target, 0, 0, used);
        return res;
    }
};
// 131 分割回文串
class Solution131 {
    vector<string> path;
    vector<vector<string>> res;
    bool isPalindrome(string &s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    void back(string s, int start) {
        if (start >= s.size()) {
            res.push_back(path);
            return;
        }
        for (int i = start; i < s.size(); i++) {
            string substr = string(s.begin() + start, s.begin() + i + 1);
            if (isPalindrome(substr)) {
                path.push_back(substr);
                back(s, i + 1);
                path.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        back(s, 0);
        return res;
    }
};
// 93 复原IP地址
class Solution93 {
    bool isValid(const string &s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start != end) {
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') {
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) {
                return false;
            }
        }
        return true;
    }
    vector<string> res;
    void back(string s, int start, int dottime) {
        if (dottime == 3) {
            if (isValid(s, start, s.size() - 1)) res.push_back(s);
            return;
        }
        for (int i = start; i < s.size(); i++) {
            if (isValid(s, start, i)) {
                s.insert(s.begin() + i + 1, '.');
                back(s, i + 2, dottime + 1);
                s.erase(s.begin() + i + 1);
            }
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        back(s, 0, 0);
        return res;
    }
};

// 78.子集
class Solution78 {
public:
    vector<int> path;
    vector<vector<int>> res;
    void back(vector<int> &nums, int start) {
        if (start >= nums.size()) {
            return;
        }
        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);
            res.push_back(path);
            back(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int> &nums) {
        res.push_back({});
        back(nums, 0);
        return res;
    }
};
// 90. 子集 II
class Solution90 {
public:
    vector<int> path;
    vector<vector<int>> res;
    void back(vector<int> &nums, int start) {
        if (start >= nums.size()) {
            return;
        }
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i - 1]) continue;
            path.push_back(nums[i]);
            res.push_back(path);
            back(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end(), [](int left, int right) { return left < right; });
        res.push_back({});
        back(nums, 0);
        return res;
    }
};
// 491. 非递减子序列
class Solution491 {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int> &nums, int startIndex) {
        if (path.size() > 1) {
            result.push_back(path);
            // 注意这里不要加return，要取树上的节点
        }
        unordered_set<int> uset; // 使用set对本层元素进行去重
        for (int i = startIndex; i < nums.size(); i++) {
            if ((!path.empty() && nums[i] < path.back()) || uset.find(nums[i]) != uset.end()) {
                continue;
            }
            uset.insert(nums[i]); // 记录这个元素在本层用过了，本层后面不能再用了
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> findSubsequences(vector<int> &nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
    class Solution {
    private:
        vector<vector<int>> result;
        vector<int> path;
        void backtracking(vector<int> &nums, int startIndex) {
            if (path.size() > 1) {
                result.push_back(path);
            }
            int used[201] = {0}; // 这里使用数组来进行去重操作，题目说数值范围[-100, 100]
            for (int i = startIndex; i < nums.size(); i++) {
                if ((!path.empty() && nums[i] < path.back()) || used[nums[i] + 100] == 1) {
                    continue;
                }
                used[nums[i] + 100] = 1; // 记录这个元素在本层用过了，本层后面不能再用了
                path.push_back(nums[i]);
                backtracking(nums, i + 1);
                path.pop_back();
            }
        }

    public:
        vector<vector<int>> findSubsequences(vector<int> &nums) {
            result.clear();
            path.clear();
            backtracking(nums, 0);
            return result;
        }
    };
};
// 46. 全排列
class Solution46 {
public:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;
    void back(vector<int> &nums) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            path.push_back(nums[i]);
            used[i] = true;
            back(nums);
            used[i] = false;
            path.pop_back();
        }
    }
    vector<vector<int>> permute(vector<int> &nums) {
        used.resize(nums.size());
        back(nums);
        return result;
    }
};
// 47.全排列 II
class Solution47 {
public:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;
    void back(vector<int> &nums) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) continue;
            path.push_back(nums[i]);
            used[i] = true;
            back(nums);
            used[i] = false;
            path.pop_back();
        }
    }
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        used.resize(nums.size());
        sort(nums.begin(), nums.end());
        back(nums);
        return result;
    }
};
// 332. 重新安排行程
class Solution332 {
public:
    int tn;
    vector<string> res;
    unordered_map<string, map<string, int>> umap;
    bool back() {
        if (res.size() == tn + 1) return true;
        for (auto &f : umap[res[res.size() - 1]]) {
            if (f.second > 0) {
                res.push_back(f.first);
                f.second--;
                if (back()) return true;
                res.pop_back();
                f.second++;
            }
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>> &tickets) {
        tn = tickets.size();
        for (const auto &ticket : tickets) {
            umap[ticket[0]][ticket[1]]++;
        }
        res.push_back("JFK");
        back();
        return res;
    }
};
// 51. N 皇后
class Solution51 {
    int nn;
    vector<vector<string>> res;
    vector<string> solve;
    bool ifRight(int row, int col, vector<string> &chessboard) {
        for (int i = 0; i < row; i++) { // 这是一个剪枝
            if (chessboard[i][col] == 'Q') {
                return false;
            }
        }
        // 检查 45度角是否有皇后
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (chessboard[i][j] == 'Q') {
                return false;
            }
        }
        // 检查 135度角是否有皇后
        for (int i = row - 1, j = col + 1; i >= 0 && j < nn; i--, j++) {
            if (chessboard[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
    void back(int row) {
        if (row >= nn) {
            res.push_back(solve);
            return;
        }
        for (int i = 0; i < nn; i++) {
            if (ifRight(row, i, solve)) {
                solve[row][i] = 'Q';
                back(row + 1);
                solve[row][i] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        nn = n;
        solve = vector<string>(nn, string(nn, '.'));
        back(0);
        return res;
    }
};
// 37. 解数独
class Solution37 {
    bool isValid(int row, int col, char val, vector<vector<char>> &board) {
        for (int i = 0; i < 9; i++) { // 判断行里是否重复
            if (board[row][i] == val) {
                return false;
            }
        }
        for (int j = 0; j < 9; j++) { // 判断列里是否重复
            if (board[j][col] == val) {
                return false;
            }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == val) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool back(vector<vector<char>> &board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] != '.') {
                    continue;
                }
                for (char k = '1'; k <= '9'; k++)
                    if (isValid(i, j, k, board)) {
                        board[i][j] = k;
                        if (back(board)) return true;
                        board[i][j] = '.';
                    }
                return false;
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>> &board) { back(board); }
};

// 455. 分发饼干
class Solution455 {
public:
    int findContentChildren(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end(), std::greater<int>());
        sort(s.begin(), s.end(), std::greater<int>());
        int num = 0, boyi = 0;
        // 饼干
        for (int i = 0; i < s.size();) {
            if (boyi >= g.size()) break;
            if (s[i] >= g[boyi]) {
                num++;
                boyi++;
                i++;
            } else {
                boyi++;
            }
        }
        return num;
    }
    int findContentChildren2(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end(), std::greater<int>());
        sort(s.begin(), s.end(), std::greater<int>());
        int num = 0, cookiei = 0;
        // 遍历小孩
        for (int i = 0; i < g.size(); i++) {
            if (cookiei < s.size() && g[i] <= s[cookiei]) {
                num++;
                cookiei++;
            }
        }
        return num;
    }
};
// 376. 摆动序列
class Solution376 {
public:
    int dp[1024][2] = {0};
    int wiggleMaxLength(vector<int> &nums) {
        dp[0][0] = dp[0][1] = 1;
        for (int i = 1; i < nums.size(); i++) {
            dp[i][0] = dp[i][1] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] > nums[i]) dp[i][1] = max(dp[i][1], dp[j][0] + 1); // 做山谷
                if (nums[j] < nums[i]) dp[i][0] = max(dp[i][0], dp[j][1] + 1);
            }
        }
        return max(dp[nums.size() - 1][0], dp[nums.size() - 1][1]);
    }
    int wiggleMaxLength2(vector<int> &nums) {
        if (nums.size() <= 1) return nums.size();
        int curDiff = 0; // 当前一对差值
        int preDiff = 0; // 前一对差值
        int result = 1;  // 记录峰值个数，序列默认序列最右边有一个峰值
        for (int i = 0; i < nums.size() - 1; i++) {
            curDiff = nums[i + 1] - nums[i];
            // 出现峰值
            if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                result++;
                preDiff = curDiff;
            }
        }
        return result;
    }
};

// 53. 最大子数组和
class Solution53 {
public:
    int maxSubArray(vector<int> &nums) {
        int sum = INT32_MIN;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            count += nums[i];
            sum = max(count, sum);
            if (count < 0) {
                count = 0;
            }
        }
        return sum;
    }
};

// 55. 跳跃游戏
class Solution55 {
public:
    bool canJump(vector<int> &nums) {
        int comm = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (comm >= i) comm = max(comm, nums[i] + i);
        }
        return comm >= nums.size() - 1;
    }
    bool canJump_std(vector<int> &nums) {
        int cover = 0;
        if (nums.size() == 1) return true;
        for (int i = 0; i <= cover; i++) {
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1) return true; // 说明可以覆盖到终点了
        }
        return false;
    }
    bool canJump2(vector<int> &nums) {
        vector<int> dp(nums.size(), 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            if (dp[i] == 1) {
                for (int j = 1; j <= nums[i] && i + j < nums.size(); j++) {
                    dp[i + j] = 1;
                }
            }
        }
        return dp[nums.size() - 1];
    }
};
// 45 跳跃游戏II
// 链接：https://leetcode.cn/problems/jump-game-ii/solutions/2926993/tu-jie-yi-zhang-tu-miao-dong-tiao-yue-yo-h2d4/
class Solution45 {
public:
    int jump(vector<int> &nums) {
        int ans = 0;
        int cur_right = 0;  // 已建造的桥的右端点
        int next_right = 0; // 下一座桥的右端点的最大值
        for (int i = 0; i + 1 < nums.size(); i++) {
            next_right = max(next_right, i + nums[i]);
            if (i == cur_right) {       // 到达已建造的桥的右端点
                cur_right = next_right; // 造一座桥
                ans++;
            }
        }
        return ans;
    }
};
// 1005. K 次取反后最大化的数组和
class Solution1005 {
public:
    int largestSumAfterKNegations(vector<int> &nums, int k) {
        int sum = 0;
        sort(nums.begin(), nums.end(), [](int left, int right) { return abs(left) > abs(right); });
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < 0 && k > 0) {
                nums[i] = -nums[i];
                k--;
            }
        }
        if (k % 2 == 1) {
            nums[nums.size() - 1] = -nums[nums.size() - 1];
        }
        for (auto &a : nums) sum += a;
        return sum;
    }
};
// 加油站
class Solution134 {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int sum = 0, cursum = 0; // sum 从i开始的剩余油的数量   curSum 总的累加
        int res = 0;
        for (int i = 0; i < gas.size(); i++) {
            sum += gas[i] - cost[i];
            cursum += gas[i] - cost[i];
            if (sum < 0) {
                res = i + 1;
                sum = 0;
            }
        }
        if (cursum < 0) return -1;
        return res;
    }
};
// 135 分发糖果
// 顾此失彼
class Solution135 {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        vector<int> can(n, 1);
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) can[i] = can[i - 1] + 1;
        }
        for (int i = n - 1; i > 0; i--) {
            if (ratings[i - 1] > ratings[i]) {
                can[i - 1] = max(can[i - 1], can[i] + 1);
            }
        }
        int result = 0;
        for (int i = 0; i < can.size(); i++) result += can[i];
        return result;
    }
};

// 860. 柠檬水找零
class Solution860 {
public:
    bool lemonadeChange(vector<int> &bills) {
        int store[2] = {0, 0}; // 0 5d 1 10d 2 20d
        for (int x : bills) {
            if (x == 5) {
                store[0]++;
            } else if (x == 10) {
                store[1]++;
                if (store[0] > 0) {
                    store[0]--;
                } else {
                    return false;
                }
            } else {
                if (store[1] > 0 && store[0] > 0) {
                    store[1]--;
                    store[0]--;
                } else if (store[0] > 2) {
                    store[0] -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
// 406. 根据身高重建队列
class Solution406 {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
        sort(people.begin(), people.end(), [](vector<int> &a, vector<int> &b) {
            if (a[0] == b[0]) return a[1] < b[1];
            return a[0] > b[0];
        });
        vector<vector<int>> que(people.size());
        for (int i = 0; i < people.size(); i++) {
            que.insert(que.begin() + people[i][1], people[i]);
        }
        return que;
    }
};
// 452. 用最少数量的箭引爆气球
class Solution452 {
public:
    int findMinArrowShots(vector<vector<int>> &points) {
        if (points.empty()) return 0;
        sort(points.begin(), points.end(), [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
        int ans = 1;
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {
                ans++;
            } else {
                points[i][1] = min(points[i][1], points[i - 1][1]);
            }
        }
        return ans;
    }
};

// 435. 无重叠区间
class Solution435 {
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        if (intervals.empty()) return 0;
        int ans = 0;
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                ans++;
                intervals[i][1] = min(intervals[i][1], intervals[i - 1][1]); // 模拟撤销的动作
            }
        }
        return ans;
    }
};

// 763.划分字母区间
class Solution763 {
public:
    vector<int> partitionLabels(string s) {
        int i = 0, j = 0;
        vector<int> res;
        unordered_map<char, int> umap;
        for (int i = 0; i < s.size(); i++) {
            if (umap.find(s[i]) != umap.end()) continue;
            umap[s[i]] = s.find_last_of(s[i]);
        }
        j = umap[s[i]]; // 右边界
        int count = 0;
        while (j < s.size()) {
            while (i < j) {
                i++;
                if (umap[s[i]] > j) j = umap[s[i]];
            }
            res.push_back(j - count + 1);
            count = ++i;
            if (i >= s.size()) break;
            j = umap[s[i]];
        }
        return res;
    }
    // 随想录写的  比我自己写的清晰很多
    class Solution {
    public:
        vector<int> partitionLabels(string s) {
            vector<int> result;
            // 记录每个字符最后一次出现的位置
            unordered_map<char, int> lastOccurrence;
            for (int i = 0; i < s.size(); i++) {
                lastOccurrence[s[i]] = i;
            }
            int start = 0; // 当前子串的起始位置
            int end = 0;   // 当前子串的结束位置
            for (int i = 0; i < s.size(); i++) {
                // 更新当前子串的结束位置
                end = max(end, lastOccurrence[s[i]]);
                // 如果当前位置等于结束位置，说明当前子串划分完成
                if (i == end) {
                    result.push_back(end - start + 1); // 记录子串长度
                    start = i + 1;                     // 开始下一个子串
                }
            }
            return result;
        }
    };
};

// 56. 合并区间
class Solution56 {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        if (intervals.size() <= 1) return intervals;
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
        vector<vector<int>> res{intervals[0]};
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            } else {
                res.push_back(intervals[i]);
            }
        }
        return res;
    }
};
// 738. 单调递增的数字
class Solution738 {
public:
    int monotoneIncreasingDigits(int n) {
        string s = to_string(n);
        int flag = s.size();
        for (int i = s.size() - 2; i >= 0; i--) {
            if (s[i] > s[i + 1]) {
                flag = i + 1;
                s[i]--;
            }
        }
        for (int i = flag; i < s.size(); i++) {
            s[i] = '9';
        }
        return stoi(s);
    }
};
// 968. 监控二叉树
class Solution968 {
    int ans = 0;

public:
    // re 1 监控装这里
    // re 2 本节点有覆盖
    // re 3 本节点无覆盖
    int travel(TreeNode *node) {
        if (!node) return 2;
        int left = travel(node->left);
        int right = travel(node->right);
        // 情况1 子节点均被覆盖
        if (left == 2 && right == 2) return 3;
        // 情况3  至多只有一个子节点被覆盖
        if (left == 3 || right == 3) {
            ans++;
            return 1;
        }
        // 情况2 某个子节点装了监控
        if (left == 1 || right == 1) return 2;
        return -1;
    }
    int minCameraCover(TreeNode *root) {
        int s = travel(root);
        if (s == 3) ans++;
        return ans;
    }
};

/**
 * @brief  DP
 *
 */

// 746. 使用最小花费爬楼梯
class Solution746 {
public:
    int minCostClimbingStairs(vector<int> &cost) {
        int n = cost.size();
        if (n <= 1) return 0;
        vector<int> dp(n + 2, 0);
        for (int i = 2; i <= n; i++) {
            dp[i + 1] = min(dp[i] + cost[i - 1], dp[i - 1] + cost[i - 2]);
        }
        return dp[n + 1];
    }
};
// 62. 不同路径
class Solution62 {
public:
    int uniquePaths2(int m, int n) {
        // 最简单的方法 一共走m+n-2步，选出m-1步走下
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
    int uniquePaths(int m, int n) {
        // 最简单的方法 一共走m+n-2步，选出m-1步走下
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] = dp[j - 1] + dp[j];
            }
        }
        return dp[n - 1];
    }
};
// 63. 不同路径 II
class Solution63 {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (obstacleGrid[m - 1][n - 1] == 1 || obstacleGrid[0][0] == 1) // 如果在起点或终点出现了障碍，直接返回0
            return 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            if (obstacleGrid[i][0] == 0)
                dp[i][0] = 1;
            else
                break;
        }
        for (int i = 0; i < n; i++) {
            if (obstacleGrid[0][i] == 0)
                dp[0][i] = 1;
            else
                break;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 0) dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
// 343. 整数拆分
class Solution343 {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int k = 1; k < i && k <= i - k; k++) {
                dp[i] = max({dp[i], dp[i - k] * dp[k], (i - k) * k, dp[i - k] * k, (i - k) * dp[k]});
            }
        }
        return dp[n];
    }
};
// 96. 不同的二叉搜索树
class Solution96 {
public:
    int numTrees(int n) {
        if (n <= 1) return 1;
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                dp[i] += dp[j] * dp[i - j - 1];
            }
        }
        return dp[n];
    }
};
// 416. 分割等和子集
class Solution416 {
public:
    bool back(vector<int> &nums, int i, int j, vector<vector<int>> &mem) {
        if (i == 0) return j == nums[0];
        bool res;
        if (mem[i][j] == -1)
            mem[i][j] = res = j >= nums[i] && back(nums, i - 1, j - nums[i], mem) || back(nums, i - 1, j, mem);
        else
            return mem[i][j];
        return res;
    }
    // 第一种方法 记忆化搜索
    bool canPartition1(vector<int> &nums) {
        int sum = 0;
        for (int x : nums) {
            sum += x;
        }
        if (sum % 2 == 1) return false;
        vector<vector<int>> mem(nums.size(), vector<int>(sum / 2 + 1, -1));
        return back(nums, nums.size() - 1, sum / 2, mem);
    }
    // 第二种方法 DP 可以看作容量为sum/2的背包，物品均是数字，重量和价值都为数值
    // 看背包装好后的最大价值
    bool canPartition(vector<int> &nums) {
        int sum = 0;
        for (int x : nums) {
            sum += x;
        }
        if (sum % 2 == 1) return false;
        vector<int> dp(sum / 2 + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            for (int j = sum / 2; j >= nums[i]; j--) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        return dp[sum / 2] == sum / 2;
    }
};

// 494 目标和
class Solution494 {
public:
    int findTargetSumWays(vector<int> &nums, int target) {
        int sum = 0;
        for (int x : nums) sum += x;
        if (abs(target) > sum) return 0;
        if ((sum + target) % 2 == 1) return 0;
        int left = (sum + target) / 2;
        // dp[i][j]：使用 下标为[0,
        // i]的nums[i]能够凑满j（包括j）这么大容量的包，有dp[i][j]种方法。
        vector<int> dp(left + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = left; j >= nums[i]; j--) {
                dp[j] = dp[j] + dp[j - nums[i]];
            }
        }
        return dp[left];
    }
};

// 474. 一和零
class Solution474 {
public:
    int findMaxForm(vector<string> &strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // dp[i][j] 有i个0和j个1的最大子集长度
        for (const string &str : strs) {
            int num0 = 0, num1 = 0;
            for (char c : str) {
                if (c == '0')
                    num0++;
                else
                    num1++;
            }
            for (int i = m; i >= num0; i--) {
                for (int j = n; j >= num1; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - num0][j - num1] + 1);
                }
            }
        }
        return dp[m][n];
    }
};

// 518. 零钱兑换 II
class Solution518 {
public:
    int change(int amount, vector<int> &coins) {
        vector<uint64_t> dp(amount + 1,
                            0); // dp[i][j] 背包载重j，截止第i个物品能凑出重量为j的方案数
        dp[0] = 1;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount];
    }
};

// 377. 组合总和 Ⅳ
class Solution377 {
public:
    int combinationSum4(vector<int> &nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int j = 0; j <= target; j++) {
            for (int i = 0; i < nums.size(); i++) {
                if (j >= nums[i]) dp[j] += dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};
// 322. 零钱兑换
class Solution322 {
public:
    int coinChange(vector<int> &coins, int amount) {
        // dp[j] 总金额截止i的时候，填满需要的最少硬币个数
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int i = 0; i < coins.size(); i++) {
            for (int j = coins[i]; j <= amount; j++) {
                if (dp[j] != -1 && dp[j - coins[i]] != -1)
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
                else if (dp[j - coins[i]] != -1)
                    dp[j] = dp[j - coins[i]] + 1;
            }
        }
        return dp[amount];
    }
};

// 279. 完全平方数
class Solution279 {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i * i <= n; i++) {
            for (int j = i * i; j <= n; j++) {
                if (dp[j - i * i] != INT_MAX) dp[j] = min(dp[j], dp[j - i * i] + 1);
            }
        }
        return dp[n];
    }
};
// 139. 单词拆分
class Solution139 {
    class Solution {
    public:
        bool wordBreak(string s, vector<string> &wordDict) {
            unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
            vector<bool> dp(s.size() + 1, false);
            dp[0] = true;
            for (int i = 1; i <= s.size(); i++) {     // 遍历背包
                for (int j = 0; j < i; j++) {         // 遍历物品
                    string word = s.substr(j, i - j); // substr(起始位置，截取的个数)
                    if (wordSet.find(word) != wordSet.end() && dp[j]) {
                        dp[i] = true;
                    }
                }
            }
            return dp[s.size()];
        }
    };
    bool check(string &s, string &c, int a, int b) {
        int t = 0;
        for (int i = a; i <= b; i++) {
            if (s[t++] != c[i]) return false;
        }
        return true;
    }

public:
    bool wordBreak(string s, vector<string> &wordDict) {
        // dp[i] 0..i-1的字符串可以被拆分
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int j = 1; j <= s.size(); j++) {
            for (int i = 0; i < wordDict.size(); i++) {
                if (j >= wordDict[i].size()) {
                    dp[j] = dp[j - wordDict[i].size()] && check(wordDict[i], s, j - wordDict[i].size(), j - 1);
                    if (dp[j]) break;
                }
            }
        }
        return dp[s.size()];
    }
};

// 198. 打家劫舍
class Solution198 {
public:
    int rob(vector<int> &nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        // dp[j] 截止到j的最大金额
        int dp0 = nums[0];
        int dp1 = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            int new_dp = max(dp1, dp0 + nums[i]);
            dp1 = new_dp;
            dp0 = dp1;
        }
        return dp1;
    }
};

class Solution213 {
public:
    int rob1(vector<int> &nums, int begin, int end) {
        // dp[j] 截止到j的最大金额
        if (begin == end) return nums[begin];
        int dp0 = 0;
        int dp1 = 0;
        for (int i = begin; i <= end; i++) {
            int new_dp = max(dp1, dp0 + nums[i]);
            dp0 = dp1;
            dp1 = new_dp;
        }
        return dp1;
    }
    int rob(vector<int> &nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        return max(rob1(nums, 1, n - 1), rob1(nums, 0, n - 2));
    }
};
// 337. 打家劫舍 III 树形DP入门
class Solution337 {
public:
    pair<int, int> travel(TreeNode *node) {
        if (!node) return {0, 0};
        auto [l, lno] = travel(node->left);
        auto [r, rno] = travel(node->right);
        return {/*选这一节点*/ node->val + lno + rno,
                /* 不选*/ max(l, lno) + max(r, rno)};
    }
    int rob(TreeNode *root) {
        auto tmp = travel(root);
        return max(tmp.first, tmp.second);
    }
};

// 121. 买卖股票的最佳时机
class Solution121 {
public:
    int maxProfit1(vector<int> &prices) {
        int premin = INT_MIN;
        int ans = 0;
        for (int i = 0; i < prices.size(); i++) {
            ans = max(prices[i] - premin, ans);
            premin = min(prices[i], premin);
        }
        return ans;
    }
    // dp
    int maxProfit(vector<int> &prices) {
        vector<vector<int>> dp(prices.size(), {0, 0});
        // dp[i][0] 第i天持有股票的最大利润
        dp[0][0] = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }
        return dp[prices.size() - 1][1];
    }
    int maxProfit_s(vector<int> &prices) {
        int f0 = -prices[0], f1 = 0;
        for (int i = 1; i < prices.size(); i++) {
            f1 = max(f1, f0 + prices[i]);
            f0 = max(f0, -prices[i]);
        }
        return f1;
    }
};

// 122 股票ii
class Solution122 {
public:
    // 贪心
    int maxProfitT(vector<int> &prices) {
        int ans = 0;
        for (int i = 1; i < prices.size(); i++) {
            ans += max(0, prices[i] - prices[i - 1]);
        }
        return ans;
    }
    // DP
    int maxProfit(vector<int> &prices) {
        int f0 = -prices[0], f1 = 0; // f0 本轮持有股票  f1 本轮bu持有股票
        for (int i = 1; i < prices.size(); i++) {
            int f0_his = f0;
            // 在121中，因为股票全程只能买卖一次
            // 而本题，因为一只股票可以买卖多次
            //  所以当第i天买入股票的时候，所持有的现金可能有之前买卖过的利润。
            f0 = max(f0, f1 - prices[i]);
            f1 = max(f1, f0_his + prices[i]);
        }
        return f1;
    }
};
// 123 股票3
class Solution123 {
public:
    int maxProfit(vector<int> &prices) {
        // dp[0] 第一次持有股票
        // dp[1] 第一次不持有股票
        // dp[2] 第二次持有股票
        // dp[3] 第二次不持有股票
        array<int, 4> dp{0};
        dp[0] = dp[2] = -prices[0];
        array<int, 4> dp_his = dp;
        for (int i = 1; i < prices.size(); i++) {
            dp[0] = max(dp_his[0], -prices[i]);
            dp[1] = max(dp_his[1], dp_his[0] + prices[i]);
            dp[2] = max(dp_his[2], dp_his[1] - prices[i]);
            dp[3] = max(dp_his[3], dp_his[2] + prices[i]);
            dp_his = dp;
        }
        return dp[3];
    }
};
// 188. 买卖股票的最佳时机 IV
class Solution188 {
public:
    int maxProfit(int k, vector<int> &prices) {
        vector<int> dp(2 * k, 0);
        for (int i = 0; i < 2 * k; i++) {
            if (i % 2 == 0) dp[i] = -prices[0];
        }
        vector<int> dp_his = dp;
        for (int j = 1; j < prices.size(); j++) {
            dp[0] = max(dp_his[0], -prices[j]);
            for (int i = 1; i < 2 * k; i++) {
                if (i % 2 == 0)
                    dp[i] = max(dp_his[i], dp_his[i - 1] - prices[j]);
                else {
                    dp[i] = max(dp_his[i], dp_his[i - 1] + prices[j]);
                }
            }
            dp_his = dp;
        }
        return dp[2 * k - 1];
    }
};

// 309. 买卖股票的最佳时机含冷冻期
class Solution309 {
public:
    int maxProfit(vector<int> &prices) {
        int f0 = -prices[0], f1 = 0, f2 = 0,
            f3 = 0; // 持有 今天卖出 冷冻期 不动期
        for (int i = 1; i < prices.size(); i++) {
            int f1h = f1;
            f3 = max(f2, f3);
            f2 = f1;
            f1 = f0 + prices[i];
            f0 = max(f0, max(f1, f3) - prices[i]);
        }
        return max(f1, max(f2, f3));
    }
};

class Solutiongp5 {
public:
    int maxProfit(vector<int> &prices, int fee) {
        int f0 = -prices[0], f1 = 0;
        for (int i = 1; i < prices.size(); i++) {
            int f0h = f0;
            f0 = max(f0, f1 - prices[i]);
            f1 = max(f1, f0h + prices[i] - fee);
        }
        return max(0, f1);
    }
};
/**
 * @brief 子序列问题系列
 *
 */
class Solution300 {
public:
    int lengthOfLIS(vector<int> &nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return ranges::max(dp);
    }
};
class Solution674 {
public:
    int findLengthOfLCIS(vector<int> &nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[i - 1]) {
                    dp[i] = dp[i - 1] + 1;
                }
            }
        }
        return ranges::max(dp);
    }
};

class Solution718 {
public:
    int findLength1(vector<int> &nums1, vector<int> &nums2) {
        int m = nums1.size(), n = nums2.size(), res = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    res = max(res, dp[i][j]);
                }
            }
        }
        return res;
    }

    int maxWindow(vector<int> &nums1, vector<int> &nums2, int start1, int start2, int len) {
        int max_len = 0, current = 0;
        for (int k = 0; k < len; k++) {
            if (nums1[start1 + k] == nums2[start2 + k]) {
                current++;
                max_len = max(max_len, current);
            } else {
                current = 0;
            }
        }
        return max_len;
    }
    int findLength(vector<int> &nums1, vector<int> &nums2) {
        int m = nums1.size(), n = nums2.size();
        int res = 0;

        // 滑动nums2对齐nums1的每个位置
        for (int i = 0; i < m; i++) {
            int len = min(m - i, n);
            int max_len = maxWindow(nums1, nums2, i, 0, len);
            res = max(res, max_len);
        }

        // 滑动nums1对齐nums2的每个位置
        for (int j = 0; j < n; j++) {
            int len = min(n - j, m);
            int max_len = maxWindow(nums1, nums2, 0, j, len);
            res = max(res, max_len);
        }

        return res;
    }
};

class Solution1143or1035 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};

class Solution053 {
public:
    int maxSubArray1(vector<int> &nums) {
        int ans = nums[0], tmp_ans = 0;
        for (int x : nums) {
            tmp_ans += x;
            ans = max(tmp_ans, ans);
            if (tmp_ans < 0) tmp_ans = 0;
        }
        return ans;
    }
    int maxSubArray(vector<int> &nums) {
        vector<int> dp(nums.size(), 0);
        int res = dp[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            res = max(res, dp[i]);
        }
        return res;
    }
};

class Solution392 {
public:
    // O(t.size())
    bool isSubsequence1(string s, string t) {
        if (s.size() > t.size()) return false;
        int i = 0, j = 0;
        while (i < s.size()) {
            if (j == t.size()) return false;
            if (s[i] == t[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        return true;
    }
    // 进阶：
    // 如果有大量输入的 S，称作 S1, S2, ...,
    //     Sk 其中 k >= 10亿，你需要依次检查它们是否为 T
    //                      的子序列。在这种情况下，你会怎样改变代码？
    bool isSubsequence2(string s, string t) {
        int n = t.size();
        if (n < s.size()) return false;
        if (s.size() == 0) return true;
        vector<vector<int>> dp(n, vector<int>(26, n));
        // dp[i][j] 下标≥i的串t中字符j的序号，如果没有则为t.size()
        // 直接返回没找到 递推：t[i]== j -> t[i][j]=i;   否则=t[i+1][j]
        dp[n - 1][t[n - 1] - 'a'] = n - 1;
        for (int i = t.size() - 2; i >= 0; i--) {
            dp[i][t[i] - 'a'] = i;
            for (int j = 'z' - 'a'; j >= 0; j--) {
                if (j != t[i] - 'a') dp[i][j] = dp[i + 1][j];
            }
        }
        // s = "abc"   t = "ahhhbfffffcdd"
        for (int i = 0, j = 0; i < s.size(); i++) {
            if (j >= t.size()) return false;
            if (dp[j][s[i] - 'a'] == n) return false;
            j = dp[j][s[i] - 'a'] + 1;
        }
        return true;
    }
    // DP
    bool isSubsequence(string s, string t) {
        if (s.size() > t.size()) return false;
        if (s.size() == 0) return true;
        int m = s.size(), n = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // dp[i][j] 是s 0...i-1 t 0...j-1 的公共串长度
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    // dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    dp[i][j] = dp[i][j - 1]; // 一般的，本题目可以只考虑删除t串的字符
            }
        }
        return dp[m][n] == s.size();
    }
};
class Solution115 {
public:
    int numDistinct1(string s, string t) {
        int m = s.size(), n = t.size();
        vector<uint64_t> dp(n + 1, 0); // dp[j] t[0...j]有多少种方式填满
        // 把t当背包，每个地方只能放对应的字符，把s的每个字符当物品 0-1背包
        dp[0] = 1;
        for (int i = 1; i <= m; i++) {      // 遍历物品 s[i-1]
            for (int j = n; j >= 1; j--) {  // 遍历背包
                if (s[i - 1] == t[j - 1]) { // 匹配了
                    dp[j] += dp[j - 1];
                }
            }
        }
        return dp[n] % 1000000007;
    }
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        if (m < n) return 0;
        // dp[i][j] s 0....i-1的子序列中t 0....j-1出现的次数
        vector dp(m + 1, vector<uint64_t>(n + 1, 0));
        // 初始化   dp[i][0] = 1
        for (int i = 0; i < m; i++) dp[i][0] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    // 选s[i-1]和t[j-1]相匹配  也可以不选
                    // bagg   bag  两者的最后一个g相同，可以不管，用bag匹配 ba
                    // 也可以不用这个g去匹配，也就是  bag匹配bag
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else
                    // 没法用s[i-1]和t[j-1]相匹配 只能不考虑s[i-1]
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[m][n];
    }
};
class Solution72 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();

        // dpi,j  使得w1 0..i-1 和 w2 0...j-1相同的最少操作数
        vector dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else {
                    // 删除等效于另一个添加
                    dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1 /*改*/});
                }
            }
        }
        return dp[m][n];
    }
};

class Solution647 {
public:
    int countSubstrings(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
                    result++;
                    dp[i][j] = true;
                }
            }
        }
        return result;
    }
    // 双指针方法
    int countSubstrings2(string s) {
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            result += extend(s, i, i, s.size());     // 以i为中心
            result += extend(s, i, i + 1, s.size()); // 以i和i+1为中心
        }
        return result;
    }
    int extend(const string &s, int i, int j, int n) {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            res++;
        }
        return res;
    }
};

class Solution516 {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(2, vector<int>(s.size(), 0));
        for (int i = 0; i < s.size(); i++) {
            dp[i % 2][i] = dp[i % 2][i] = 1;
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            for (int j = i + 1; j < s.size(); j++) {
                if (s[i] == s[j])
                    dp[i % 2][j] = dp[(i + 1) % 2][j - 1] + 2;
                else
                    dp[i % 2][j] = max(dp[(i + 1) % 2][j], dp[i % 2][j - 1]);
            }
        }
        return dp[0][s.size() - 1];
    }
};

class 单调栈_从右到左 {
public:
    vector<int> dailyTemperatures(vector<int> &temperatures) {
        stack<int> st;
        vector ans(temperatures.size(), 0);
        for (int i = temperatures.size() - 1; i >= 0; i--) {
            while (!st.empty() && temperatures[i] >= temperatures[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                ans[i] = st.top() - i;
            }
            st.push(i);
        }
        return ans;
    }
};

class 单调栈_从左到右 {
public:
    vector<int> dailyTemperatures(vector<int> &temperatures) {
        stack<int> st;
        vector ans(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};

class 接雨水单调栈 {
public:
    int trap(vector<int> &height) {
        int ans = 0;
        stack<int> st;
        for (int i = 0; i < height.size(); i++) {
            // >=可以减少空间复杂度
            while (!st.empty() && height[i] >= height[st.top()]) {
                int h_bottom = height[st.top()];
                st.pop();
                if (st.empty()) break;
                int w = i - st.top() - 1;
                int h = min(height[i], height[st.top()]) - h_bottom;
                ans += w * h;
            }
            st.push(i);
        }
        return ans;
    }
};
class 接雨水前后缀 {
public:
    int trap(vector<int> &height) {
        if (height.size() <= 2) return 0;
        int maxLeft = height[0];
        vector<int> maxRight(height.size(), 0);
        int size = maxRight.size();

        // 前缀和求和同时算
        //  记录每个柱子右边柱子最大高度
        maxRight[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            maxRight[i] = max(height[i], maxRight[i + 1]);
        }
        // 求和
        int sum = 0;
        for (int i = 1; i < size - 1; i++) {
            int count = min(maxLeft, maxRight[i]) - height[i];
            if (count > 0) sum += count;
            maxLeft = max(height[i], maxLeft);
        }
        return sum;
    }
};
class 下一个更大的元素I {
public:
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {
        unordered_map<int, int> idx;
        for (int i = 0; i < nums1.size(); i++) {
            idx[nums1[i]] = i;
        }
        stack<int> st;
        vector<int> res(nums1.size(), -1);
        for (int i = 0; i < nums2.size(); i++) {
            int num = nums2[i];
            while (!st.empty() && num > st.top()) {
                res[idx[st.top()]] = num;
                st.pop();
            }
            if (idx.contains(num)) st.push(num);
        }
        return res;
    }
};
class 下一个更大的元素II {
public:
    vector<int> nextGreaterElements(vector<int> &nums) {
        vector<int> res(nums.size() * 2, 0);
        stack<int> st;
        for (int i = 0; i < 2 * nums.size(); i++) {
            int num = nums[i % nums.size()];
            while (!st.empty() && num > nums[st.top()]) {
                res[st.top()] = num;
                st.pop();
            }
            st.push(i % nums.size());
        }
        return vector<int>(nums.begin(), nums.begin() + nums.size());
    }
};

class 单调栈完结 {
public:
    int largestRectangleArea(vector<int> &heights) {
        int n = heights.size();
        vector left(n, -1);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                left[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>{};
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && heights[i] <= heights[st.top()]) {
                st.pop();
            }
            if (!st.empty())
                ans = max(ans, heights[i] * (st.top() - 1 - left[i]));
            else
                ans = max(ans, heights[i] * (n - 1 - left[i]));
            st.push(i);
        }
        return ans;
    }
};