<<<<<<< HEAD
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
class Solution707 {
public:
    int search(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (nums[middle] > target) { right = middle - 1; }
            else if (nums[middle] < target) { left = middle + 1; }
            else { return middle; }
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
            if (nums[fast] != val) { nums[slow++] = nums[fast]; }
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
            }
            else {
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
            for (int i = left; i <= right; i++) { res[top][i] = m++; }
            top++;
            for (int j = top; j <= bottom; j++) { res[j][right] = m++; }
            right--;
            for (int k = right; k >= left; k--) { res[bottom][k] = m++; }
            bottom--;
            for (int x = bottom; x >= top; x--) { res[x][left] = m++; }
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
            }
            else { cur = cur->next; }
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
        if (index < 0 || index > (_size - 1)) { return -1; }
        node *tmp = _dummyHead->next;
        while (index--) { tmp = tmp->next; }
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
        while (cur->next != nullptr) { cur = cur->next; }
        cur->next = newNode;
        _size++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0) index = 0;
        if (index > (_size)) { return; }
        node *cur = _dummyHead;
        while (index--) { cur = cur->next; }
        node *tmp = new node(val, cur->next);
        cur->next = tmp;
        _size++;
        return;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index > (_size - 1)) return;
        node *cur = _dummyHead;
        while (index--) { cur = cur->next; }
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
        while (n--) { fast = fast->next; }
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
        for (int i = 0; i < s.size(); i++) { a[s[i] - 'a']++; }
        for (int i = 0; i < s.size(); i++) { a[t[i] - 'a']--; }
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
        if (lenA < lenB) { swap(curA, curB); }
        int dlen = abs(lenA - lenB);
        while (dlen--) { curA = curA->next; }
        while (curA) {
            if (curA == curB) { return curA; }
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
            if (inter.find(num) != inter.end()) { res.insert(num); }
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
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                     vector<int> &nums4) {
        unordered_map<int, int> umap;
        int count = 0;
        for (int a : nums1) {
            for (int b : nums2) { umap[a + b]++; }
        }

        for (int c : nums3) {
            for (int d : nums4) {
                if (umap.find(-(c + d)) != umap.end()) { count += umap[-(c + d)]; }
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
        for (char i : magazine) { umap[i]++; }
        for (char j : ransomNote) {
            if (umap.find(j) == umap.end()) { return false; }
            else {
                umap[j]--;
                if (umap[j] < 0) return false;
            }
        }
        return true;
    }
    // 用数组其实就行
    bool canConstruct(string ransomNote, string magazine) {
        int record[26] = {0};
        for (char i : magazine) { record[i - 'a']++; }
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
                    while (left < right && nums[right] == nums[right - 1]) { right--; }
                    while (left < right && nums[left] == nums[left + 1]) { left++; }
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
        for (int i = a, j = b; i < j; i++, j--) { swap(s[i], s[j]); }
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
            if (i == s.size() - 1) { reverseS(s, a, i); }
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
            while (j > 0 && s[i] != s[j]) { j = next[j - 1]; } // 前后缀不同
            if (s[i] == s[j]) { j++; }                         // 找到相同的前后缀
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
            while (j > 0 && haystack[i] != needle[j]) { j = next[j - 1]; }
            if (haystack[i] == needle[j]) { j++; }
            if (j == needle.size()) { return (i - needle.size() + 1); }
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
        if (!out.empty()) { return out.top(); }
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
            if (!st.empty() && st.top() == c) { st.pop(); }
            else if (c == '(')
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
            }
            else { st.push(stoll(tokens[i])); }
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
            while (!Q.empty() && c > Q.back()) { Q.pop_back(); }
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
        for (int i = 0; i < k; i++) { mq.push(nums[i]); }
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
        for (int num : nums) { map[num]++; }
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
            return lhs.second > rhs.second;
        });
        vector<int> a(k);
        for (int i = 0; i < k; ++i) { a[i] = vec[i].first; }
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

    //     // 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
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
            }
            else {
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
    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
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
                if (cur->left) { q.push(cur->left); }
                if (cur->right) { q.push(cur->right); }
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
        if (root->left) { res1 = hasPathSum(root->left, targetSum - root->val); }
        if (root->right) { res2 = hasPathSum(root->right, targetSum - root->val); }
        return res1 || res2;
    }
    bool hasPathSum2(TreeNode *root, int targetSum) {
        stack<pair<TreeNode *, int>> st;
        if (!root) return false;
        st.push({root, targetSum});
        while (!st.empty()) {
            pair<TreeNode *, int> pcur = st.top();
            st.pop();
            if (pcur.first->val == pcur.second && !pcur.first->left && !pcur.first->right)
                return true;
            if (pcur.first->left) { st.push({pcur.first->left, pcur.second - pcur.first->val}); }
            if (pcur.first->right) { st.push({pcur.first->right, pcur.second - pcur.first->val}); }
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
        TreeNode *traversal(vector<int> &inorder, int inorderBegin, int inorderEnd,
                            vector<int> &postorder, int postorderBegin, int postorderEnd) {
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
            int leftPostorderEnd = postorderBegin + delimiterIndex -
                                   inorderBegin; // 终止位置是 需要加上 中序区间的大小size
            // 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
            int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);
            int rightPostorderEnd = postorderEnd - 1; // 排除最后一个元素，已经作为节点了

            root->left = traversal(inorder, leftInorderBegin, leftInorderEnd, postorder,
                                   leftPostorderBegin, leftPostorderEnd);
            root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, postorder,
                                    rightPostorderBegin, rightPostorderEnd);

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
            if (inorder[i] == rootval) { split = i; }
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
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        return traversal(nums, 0, nums.size());
    }
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
        if (t1 == NULL) return t2;                  // 如果t1为空，合并之后就应该是t2
        if (t2 == NULL) return t1;                  // 如果t2为空，合并之后就应该是t1
        t1->val += t2->val;                         // 中
        t1->left = mergeTrees2(t1->left, t2->left); // 左
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
        if (pre) { delta = min(delta, cur->val - pre->val); }
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
            }
            else {
                st.pop();
                cur = st.top();
                st.pop();
                if (pre) { delta = min(delta, cur->val - pre->val); }
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
        if (!pre) { f = 1; } // 第一个非空节点
        else if (root->val == pre->val) { f++; }
        else { // 3 3 4（遇到了这个节点） 4
            f = 1;
        }
        // 再处理具体的众数
        if (f > maxf) {
            maxf = f;
            res.clear();
            res.push_back(root->val);
        }
        else if (f == maxf) { res.push_back(root->val); }
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
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        return travel(root, p, q);
    }
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
            else if (root->left && !root->right) { return root->left; }
            else if (!root->left && root->right) { return root->right; }
            // 左右都不空
            else {
                TreeNode *rootLeft = root->left;
                TreeNode *rootRight = root->right;
                root = root->right;
                while (root->left) { root = root->left; }
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
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        return travel(nums, 0, nums.size() - 1);
    }
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
        if (pre) { root->val += pre->val; }
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
    void getCombinations(const string &digits, int index, const string &s) { // 注意参数的不同
        if (index == digits.size()) {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0';
        string letters = letterMap[digit];
        for (int i = 0; i < letters.size(); i++) {
            getCombinations(digits, index + 1, s + letters[i]); // 注意这里的不同
        }
    }
    vector<string> letterCombinations(string digits) {
        result.clear();
        if (digits.size() == 0) { return result; }
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
        if (start > end) { return false; }
        if (s[start] == '0' && start != end) { return false; }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { return false; }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { return false; }
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
        if (start >= nums.size()) { return; }
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
        if (start >= nums.size()) { return; }
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
            if (path.size() > 1) { result.push_back(path); }
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
        for (const auto &ticket : tickets) { umap[ticket[0]][ticket[1]]++; }
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
            if (chessboard[i][col] == 'Q') { return false; }
        }
        // 检查 45度角是否有皇后
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (chessboard[i][j] == 'Q') { return false; }
        }
        // 检查 135度角是否有皇后
        for (int i = row - 1, j = col + 1; i >= 0 && j < nn; i--, j++) {
            if (chessboard[i][j] == 'Q') { return false; }
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
            if (board[row][i] == val) { return false; }
        }
        for (int j = 0; j < 9; j++) { // 判断列里是否重复
            if (board[j][col] == val) { return false; }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == val) { return false; }
            }
        }
        return true;
    }

public:
    bool back(vector<vector<char>> &board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] != '.') { continue; }
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
            }
            else { boyi++; }
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
            if (count < 0) { count = 0; }
        }
        return sum;
    }
};
// 122. 买卖股票的最佳时机 II
class Solution122 {
public:
    int maxProfit2(vector<int> &prices) {
        int profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            if ((prices[i] - prices[i - 1]) > 0) profit += prices[i] - prices[i - 1];
        }
        return profit;
    }
    // DP
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        int dp[n][2];
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        // dp[i][0] 第i天持有股票的最大现金
        // dp[i][1] 第i天不持有股票的最大现金
        for (int i = 1; i < prices.size(); i++) {
            dp[i][1] = max(prices[i] - dp[i - 1][0], dp[i - 1][1]);
            dp[i][0] = max(dp[i - 1][0], -prices[i] + dp[i - 1][1]);
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
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
                for (int j = 1; j <= nums[i] && i + j < nums.size(); j++) { dp[i + j] = 1; }
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
        if (k % 2 == 1) { nums[nums.size() - 1] = -nums[nums.size() - 1]; }
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
class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        vector<int> can(n, 1);
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) can[i] = can[i - 1] + 1;
        }
        for (int i = n - 1; i > 0; i--) {
            if (ratings[i - 1] > ratings[i]) { can[i - 1] = max(can[i - 1], can[i] + 1); }
        }
        int result = 0;
        for (int i = 0; i < can.size(); i++) result += can[i];
        return result;
    }
};
=======
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
class Solution707 {
public:
    int search(vector<int> &nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (nums[middle] > target) { right = middle - 1; }
            else if (nums[middle] < target) { left = middle + 1; }
            else { return middle; }
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
            if (nums[fast] != val) { nums[slow++] = nums[fast]; }
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
            }
            else {
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
            for (int i = left; i <= right; i++) { res[top][i] = m++; }
            top++;
            for (int j = top; j <= bottom; j++) { res[j][right] = m++; }
            right--;
            for (int k = right; k >= left; k--) { res[bottom][k] = m++; }
            bottom--;
            for (int x = bottom; x >= top; x--) { res[x][left] = m++; }
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
            }
            else { cur = cur->next; }
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
        if (index < 0 || index > (_size - 1)) { return -1; }
        node *tmp = _dummyHead->next;
        while (index--) { tmp = tmp->next; }
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
        while (cur->next != nullptr) { cur = cur->next; }
        cur->next = newNode;
        _size++;
    }

    void addAtIndex(int index, int val) {
        if (index < 0) index = 0;
        if (index > (_size)) { return; }
        node *cur = _dummyHead;
        while (index--) { cur = cur->next; }
        node *tmp = new node(val, cur->next);
        cur->next = tmp;
        _size++;
        return;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index > (_size - 1)) return;
        node *cur = _dummyHead;
        while (index--) { cur = cur->next; }
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
        while (n--) { fast = fast->next; }
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
        for (int i = 0; i < s.size(); i++) { a[s[i] - 'a']++; }
        for (int i = 0; i < s.size(); i++) { a[t[i] - 'a']--; }
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
        if (lenA < lenB) { swap(curA, curB); }
        int dlen = abs(lenA - lenB);
        while (dlen--) { curA = curA->next; }
        while (curA) {
            if (curA == curB) { return curA; }
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
            if (inter.find(num) != inter.end()) { res.insert(num); }
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
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                     vector<int> &nums4) {
        unordered_map<int, int> umap;
        int count = 0;
        for (int a : nums1) {
            for (int b : nums2) { umap[a + b]++; }
        }

        for (int c : nums3) {
            for (int d : nums4) {
                if (umap.find(-(c + d)) != umap.end()) { count += umap[-(c + d)]; }
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
        for (char i : magazine) { umap[i]++; }
        for (char j : ransomNote) {
            if (umap.find(j) == umap.end()) { return false; }
            else {
                umap[j]--;
                if (umap[j] < 0) return false;
            }
        }
        return true;
    }
    // 用数组其实就行
    bool canConstruct(string ransomNote, string magazine) {
        int record[26] = {0};
        for (char i : magazine) { record[i - 'a']++; }
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
                    while (left < right && nums[right] == nums[right - 1]) { right--; }
                    while (left < right && nums[left] == nums[left + 1]) { left++; }
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
        for (int i = a, j = b; i < j; i++, j--) { swap(s[i], s[j]); }
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
            if (i == s.size() - 1) { reverseS(s, a, i); }
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
            while (j > 0 && s[i] != s[j]) { j = next[j - 1]; } // 前后缀不同
            if (s[i] == s[j]) { j++; }                         // 找到相同的前后缀
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
            while (j > 0 && haystack[i] != needle[j]) { j = next[j - 1]; }
            if (haystack[i] == needle[j]) { j++; }
            if (j == needle.size()) { return (i - needle.size() + 1); }
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
        if (!out.empty()) { return out.top(); }
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
            if (!st.empty() && st.top() == c) { st.pop(); }
            else if (c == '(')
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
            }
            else { st.push(stoll(tokens[i])); }
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
            while (!Q.empty() && c > Q.back()) { Q.pop_back(); }
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
        for (int i = 0; i < k; i++) { mq.push(nums[i]); }
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
        for (int num : nums) { map[num]++; }
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
            return lhs.second > rhs.second;
        });
        vector<int> a(k);
        for (int i = 0; i < k; ++i) { a[i] = vec[i].first; }
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

    //     // 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
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
            }
            else {
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
    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
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
                if (cur->left) { q.push(cur->left); }
                if (cur->right) { q.push(cur->right); }
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
        if (root->left) { res1 = hasPathSum(root->left, targetSum - root->val); }
        if (root->right) { res2 = hasPathSum(root->right, targetSum - root->val); }
        return res1 || res2;
    }
    bool hasPathSum2(TreeNode *root, int targetSum) {
        stack<pair<TreeNode *, int>> st;
        if (!root) return false;
        st.push({root, targetSum});
        while (!st.empty()) {
            pair<TreeNode *, int> pcur = st.top();
            st.pop();
            if (pcur.first->val == pcur.second && !pcur.first->left && !pcur.first->right)
                return true;
            if (pcur.first->left) { st.push({pcur.first->left, pcur.second - pcur.first->val}); }
            if (pcur.first->right) { st.push({pcur.first->right, pcur.second - pcur.first->val}); }
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
        TreeNode *traversal(vector<int> &inorder, int inorderBegin, int inorderEnd,
                            vector<int> &postorder, int postorderBegin, int postorderEnd) {
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
            int leftPostorderEnd = postorderBegin + delimiterIndex -
                                   inorderBegin; // 终止位置是 需要加上 中序区间的大小size
            // 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
            int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);
            int rightPostorderEnd = postorderEnd - 1; // 排除最后一个元素，已经作为节点了

            root->left = traversal(inorder, leftInorderBegin, leftInorderEnd, postorder,
                                   leftPostorderBegin, leftPostorderEnd);
            root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, postorder,
                                    rightPostorderBegin, rightPostorderEnd);

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
            if (inorder[i] == rootval) { split = i; }
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
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        return traversal(nums, 0, nums.size());
    }
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
        if (t1 == NULL) return t2;                  // 如果t1为空，合并之后就应该是t2
        if (t2 == NULL) return t1;                  // 如果t2为空，合并之后就应该是t1
        t1->val += t2->val;                         // 中
        t1->left = mergeTrees2(t1->left, t2->left); // 左
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
        if (pre) { delta = min(delta, cur->val - pre->val); }
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
            }
            else {
                st.pop();
                cur = st.top();
                st.pop();
                if (pre) { delta = min(delta, cur->val - pre->val); }
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
        if (!pre) { f = 1; } // 第一个非空节点
        else if (root->val == pre->val) { f++; }
        else { // 3 3 4（遇到了这个节点） 4
            f = 1;
        }
        // 再处理具体的众数
        if (f > maxf) {
            maxf = f;
            res.clear();
            res.push_back(root->val);
        }
        else if (f == maxf) { res.push_back(root->val); }
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
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        return travel(root, p, q);
    }
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
            else if (root->left && !root->right) { return root->left; }
            else if (!root->left && root->right) { return root->right; }
            // 左右都不空
            else {
                TreeNode *rootLeft = root->left;
                TreeNode *rootRight = root->right;
                root = root->right;
                while (root->left) { root = root->left; }
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
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        return travel(nums, 0, nums.size() - 1);
    }
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
        if (pre) { root->val += pre->val; }
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
    void getCombinations(const string &digits, int index, const string &s) { // 注意参数的不同
        if (index == digits.size()) {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0';
        string letters = letterMap[digit];
        for (int i = 0; i < letters.size(); i++) {
            getCombinations(digits, index + 1, s + letters[i]); // 注意这里的不同
        }
    }
    vector<string> letterCombinations(string digits) {
        result.clear();
        if (digits.size() == 0) { return result; }
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
    class Solution {
        bool isPalindrome(string &s, int left, int right) {
            while (left < right) {
                if (s[left++] != s[right--]) { return false; }
            }
            return true;
        }

    public:
        vector<vector<string>> partition(string s) {
            int n = s.length();
            vector<vector<string>> ans;
            vector<string> path;

            // start 表示当前这段回文子串的开始位置
            auto dfs = [&](auto &&dfs, int i, int start) {
                if (i == n) {
                    ans.emplace_back(path);
                    return;
                }

                // 不选 i 和 i+1 之间的逗号（i=n-1 时一定要选）
                if (i < n - 1) { dfs(dfs, i + 1, start); }

                // 选 i 和 i+1 之间的逗号（把 s[i] 作为子串的最后一个字符）
                if (isPalindrome(s, start, i)) {
                    path.push_back(s.substr(start, i - start + 1));
                    dfs(dfs, i + 1, i + 1); // 下一个子串从 i+1 开始
                    path.pop_back();        // 恢复现场
                }
            };

            dfs(dfs, 0, 0);
            return ans;
        }
    };

    // 链接：https://leetcode.cn/problems/palindrome-partitioning/solutions/2059414/hui-su-bu-hui-xie-tao-lu-zai-ci-pythonja-fues/

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
        if (start > end) { return false; }
        if (s[start] == '0' && start != end) { return false; }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { return false; }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { return false; }
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
        if (start >= nums.size()) { return; }
        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);
            res.push_back(path);
            back(nums, i + 1);
            path.pop_back();
        }
    }
    void back2(vector<int> &nums, int i) {
        if (i >= nums.size()) {
            res.push_back(path);
            return;
        }
        back2(nums, i + 1);
        path.push_back(nums[i]);
        back2(nums, i + 1);
        path.pop_back();
    }
    vector<vector<int>> subsets(vector<int> &nums) {
        back2(nums, 0);
        return res;
    }
};
// 90. 子集 II
class Solution90 {
public:
    vector<int> path;
    vector<vector<int>> res;
    void back(vector<int> &nums, int start) {
        if (start >= nums.size()) { return; }
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
            if (path.size() > 1) { result.push_back(path); }
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
        for (const auto &ticket : tickets) { umap[ticket[0]][ticket[1]]++; }
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
            if (chessboard[i][col] == 'Q') { return false; }
        }
        // 检查 45度角是否有皇后
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (chessboard[i][j] == 'Q') { return false; }
        }
        // 检查 135度角是否有皇后
        for (int i = row - 1, j = col + 1; i >= 0 && j < nn; i--, j++) {
            if (chessboard[i][j] == 'Q') { return false; }
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
            if (board[row][i] == val) { return false; }
        }
        for (int j = 0; j < 9; j++) { // 判断列里是否重复
            if (board[j][col] == val) { return false; }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == val) { return false; }
            }
        }
        return true;
    }

public:
    bool back(vector<vector<char>> &board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] != '.') { continue; }
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
            }
            else { boyi++; }
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
            if (count < 0) { count = 0; }
        }
        return sum;
    }
};
// 122. 买卖股票的最佳时机 II
class Solution122 {
public:
    int maxProfit2(vector<int> &prices) {
        int profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            if ((prices[i] - prices[i - 1]) > 0) profit += prices[i] - prices[i - 1];
        }
        return profit;
    }
    // DP
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        int dp[n][2];
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        // dp[i][0] 第i天持有股票的最大现金
        // dp[i][1] 第i天不持有股票的最大现金
        for (int i = 1; i < prices.size(); i++) {
            dp[i][1] = max(prices[i] - dp[i - 1][0], dp[i - 1][1]);
            dp[i][0] = max(dp[i - 1][0], -prices[i] + dp[i - 1][1]);
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
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
                for (int j = 1; j <= nums[i] && i + j < nums.size(); j++) { dp[i + j] = 1; }
            }
        }
        return dp[nums.size() - 1];
    }
};
// 45 跳跃游戏II
//链接：https://leetcode.cn/problems/jump-game-ii/solutions/2926993/tu-jie-yi-zhang-tu-miao-dong-tiao-yue-yo-h2d4/
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
class Solution {
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
        if (k % 2 == 1) { nums[nums.size() - 1] = -nums[nums.size() - 1]; }
        for (auto &a : nums) sum += a;
        return sum;
    }
};
int main() {
    vector<int> a{-4, 4, -3, 3, -4, -1, 8, -7, -7};
    Solution().largestSumAfterKNegations(a, 2);
}
>>>>>>> a6d8de3 (暂存本地修改)
