#include <algorithm>
#include <iostream>
#include <list>
#include <stack>
#include <unordered_set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class FindElements {
    unordered_set<int> valSet;

public:
    void build(TreeNode *root, int val) {
        if (!root) return;
        root->val = val;
        valSet.insert(val);
        if (root->left) build(root->left, 2 * root->val + 1);
        if (root->right) build(root->left, 2 * root->val + 2);
    }
    FindElements(TreeNode *root) { build(root, 0); }

    bool find(int target) { return valSet.count(target) == 1; }
};

class FinalString {
public:
    void reverse(string &s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
    string finalString(string s) {
        string res;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'i') { reverse(res); }
            else { res.push_back(s[i]); }
        }
        return res;
    }
};
class MyHashMap {
public:
    MyHashMap() {}

    void put(int key, int value) {}

    int get(int key) {}

    void remove(int key) {}
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

class MyHashSet {
private:
    vector<list<int>> data;
    static const int base = 769;
    static int hash(int key) { return key % base; }

public:
    MyHashSet() : data(base) {}

    void add(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key) return;
        }
        data[h].push_back(key);
    }

    void remove(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key) {
                data[h].erase(it);
                return;
            }
        }
    }

    bool contains(int key) {
        int h = hash(key);
        for (auto it = data[h].begin(); it != data[h].end(); it++) {
            if ((*it) == key) { return true; }
        }
        return false;
    }
};

// 2502. 设计内存分配器

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */
class MyAllocator {
    vector<int> array_;
    vector<vector<int>> check_;
    int n_;

public:
    MyAllocator(int n) : n_(n), array_(n) {}

    int allocate(int size, int mID) {
        if (size <= 0 || size > n_) return -1;
        vector<vector<int>> can;
        if (check_.empty()) { can.push_back({0, n_ - 1}); }
        else {
            int begin1 = check_[0][0];
            int end1 = check_[0][1];
            if (begin1 > 0) { can.push_back({0, begin1 - 1}); }
            for (int i = 1; i < check_.size(); i++) {
                int begin2 = check_[i][0];
                int end2 = check_[i][1];
                if (begin2 > end1 + 1) can.push_back({end1 + 1, begin2 - 1});
                begin1 = begin2;
                end1 = end2;
            }
            if (end1 < n_ - 1) { can.push_back({end1 + 1, n_ - 1}); }
        }
        for (auto &block : can) {
            int start = block[0];
            int end = block[1];
            int available_size = end - start + 1;
            if (available_size >= size) {
                // 分配内存，并插入到 check_ 的正确位置以保持有序
                vector<int> new_block = {start, start + size - 1, mID};
                auto insert_pos = lower_bound(
                    check_.begin(), check_.end(), new_block,
                    [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
                check_.insert(insert_pos, new_block);

                // 标记内存为 mID
                fill(array_.begin() + start, array_.begin() + start + size, mID);
                return start; // 返回分配的内存起始位置
            }
        }
        return -1;
    }
    int freeMemory(int mID) {
        int count = 0;
        // 遍历 check_，释放所有标记为 mID 的内存块
        for (auto it = check_.begin(); it != check_.end();) {
            if ((*it)[2] == mID) {
                // 标记内存为 0
                for (int i = (*it)[0]; i <= (*it)[1]; i++) { array_[i] = 0; }
                it = check_.erase(it); // 从 check_ 中移除该内存块
                count++;
            }
            else { it++; }
        }
        return count; // 返回释放的内存块数量
    }
};

// 作者：力扣官方题解
class Allocator {
public:
    Allocator(int n) : n(n), memory(n) {}

    int allocate(int size, int mID) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (memory[i]) { count = 0; }
            else {
                ++count;
                if (count == size) {
                    for (int j = i - count + 1; j <= i; ++j) { memory[j] = mID; }
                    return i - count + 1;
                }
            }
        }
        return -1;
    }

    int freeMemory(int mID) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (memory[i] == mID) {
                ++count;
                memory[i] = 0;
            }
        }
        return count;
    }

private:
    int n;
    vector<int> memory;
};

class BrowserHistory {
    stack<string> stack1;
    stack<string> stack2;

public:
    BrowserHistory(string homepage) { stack1.push(homepage); }

    void visit(string url) {
        stack1.push(url);
        while (!stack2.empty()) { stack2.pop(); }
    };

    string back(int steps) {
        while (steps--) {
            if (stack1.size() <= 1) break;
            stack2.push(stack1.top());
            stack1.pop();
        }
        return stack1.top();
    }

    string forward(int steps) {
        while (steps--) {
            if (stack2.empty()) break;
            stack1.push(stack2.top());
            stack2.pop();
        }
        return stack1.top();
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */
class TextEditor {
    vector<char> texts;

public:
    TextEditor() : texts(1, '|') {}

    void addText(string text) {
        for (auto it = texts.begin(); it != texts.end();) {
            if (*it == '|') {
                texts.insert(it, text.begin(), text.end());
                break;
            }
        }
        cout << text;
    }

    int deleteText(int k) {}

    string cursorLeft(int k) {}

    string cursorRight(int k) {}
};

int main() {
    string s = "aafasaf";
    TextEditor().addText(s);
}
