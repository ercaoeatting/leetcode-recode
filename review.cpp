#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <type_traits>
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
            while (j > 0 && s[i] != s[j]) { j = next[j - 1]; } //前后缀不同
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
            if (!Q.empty() && c == Q.front()) //我感觉这里才是精华，能知道要不要弹出
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

    vector<int> topKFrequent1(vector<int> &nums, int k) { //十足的笨办法  复杂度nlogn
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

    vector<int> topKFrequent(vector<int> &nums, int k) { //复杂度nlogk
        // 要统计元素出现频率
        unordered_map<int, int> map; // map<nums[i],对应出现的次数>
        for (int i = 0; i < nums.size(); i++) { map[nums[i]]++; }

        // 对频率排序
        // 定义一个小顶堆，大小为k
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<int>> pri_que;

        // 用固定大小为k的小顶堆，扫面所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
            pri_que.push(*it);
            if (pri_que.size() > k) { // 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
                pri_que.pop();
            }
        }

        // 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }
        return result;
    }
};
//二叉树
// 144 前序
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
//层序遍历102
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
class Solution {
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
                if(cur->left && cur->right) maxdep++;
                q.pop();
            }
        }
        return maxdep;
    }
};
int main() { vector<string> a{"2", "1", "+", "3", "*"}; }