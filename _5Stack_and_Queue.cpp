#include <algorithm>
#include <deque>
#include <stack>
#include <Queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
using namespace std;
class MyQueue {
private:
    stack<int> stackIn;
    stack<int> stackOut;

public:
    MyQueue() {
        stackIn = stack<int>();
        stackOut = stack<int>();
    }

    void push(int x) { stackIn.push(x); }

    int pop() {
        if (stackOut.empty()) {
            while (!stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
        int ret = stackOut.top();
        stackOut.pop();
        return ret;
    }

    int peek() {
        // return stackOut.top(); stackOut是可能为空的
        int res = this->pop(); // 直接使用已有的pop函数
        stackOut.push(res);    // 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }

    bool empty() { return !(stackIn.empty() && stackOut.empty()); }
};
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// 你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty
class MyStack {
public:
    queue<int> queue_;

    MyStack() {}

    void push(int x) { queue_.push(x); }

    int pop() {
        int size = queue_.size();
        size--;
        while (size--) {
            queue_.push(queue_.front());
            queue_.pop();
        }
        int res = queue_.front();
        queue_.pop();
        return res;
    }

    int top() { return queue_.back(); }

    bool empty() { return queue_.empty(); }
};
class lc20 {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) { return false; }
        stack<char> st;
        for (auto &i : s) {
            if (i == '(') { st.push(')'); }
            else if (i == '[') { st.push(']'); }
            else if (i == '{') { st.push('}'); }
            else if (st.empty() || st.top() != i) { return false; }
            else { st.pop(); }
        }
        return st.empty();
    }
};
class lc1047 {
public:
    string removeDuplicates(string s) {
        stack<char> result;
        for (auto &word : s) {
            if (!result.empty() && result.top() != word) { result.push(word); }
            else if (!result.empty() && result.top() == word) { result.pop(); }
            else if (result.empty()) { result.push(word); }
        }
        string str = "";
        while (!result.empty()) {
            str.push_back(result.top());
            result.pop();
        }
        reverse(str.begin(), str.end());
        return str;
    }
};
class lc150 {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> res;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int tmp1 = res.top();
                res.pop();
                int tmp2 = res.top();
                res.pop();
                if (tokens[i] == "+") { res.push(tmp1 + tmp2); }
                else if (tokens[i] == "-") { res.push(tmp2 - tmp1); }
                else if (tokens[i] == "*") { res.push(tmp1 * tmp2); }
                else if (tokens[i] == "/") { res.push(tmp2 / tmp1); }
            }
            else { res.push(stoi(tokens[i])); }
        }
        return res.top();
    }
};
class lc239 {
private:
    class MonotoneQueue {
    public:
        deque<int> deque;
        void pop(int n) {
            if (!deque.empty() && n == deque.front()) { deque.pop_front(); }
        }
        void push(int n) {
            while (!deque.empty() && n >= deque.back()) { deque.pop_back(); }
            deque.push_back(n);
        }
        int front() { return deque.front(); }
    };

public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        MonotoneQueue que;
        vector<int> res;
        for (int i = 0; i < k; i++) { que.push(nums[i]); }
        res.push_back(que.front());
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]);
            que.push(nums[i]);
            res.push_back(que.front());
        }
        return res;
    }
};
class lc347 {
public:
    struct myComp {
        bool operator()(const pair<int, int> &left, const pair<int, int> &right) {
            return left.second > right.second;
        }
    };
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> count;
        for (auto &i : nums) { ++count[i]; }
        priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> pri;
        for (auto &i : count) {
            pri.push(i);
            if (pri.size() > k) { pri.pop(); }
        }
        vector<int> result;
        for (int i = k - 1; i >= 0; i--) {
            result.push_back(pri.top().first);
            pri.pop();
        }
        return result;
    }
};

int main() {}