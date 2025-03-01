#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <stack>
#include <unordered_map>
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
    vector<char>::iterator cursor;

public:
    TextEditor() { cursor = texts.end(); }

    void addText(string text) {
        for (char c : text) { texts.insert(cursor, c); }
    }

    int deleteText(int k) {
        int count = 0;
        while (k-- && cursor != texts.begin()) {
            texts.erase(prev(cursor));
            count++;
        }
        return count;
    }

    string cursorLeft(int k) {
        while (cursor != texts.begin() && k--) { cursor = prev(cursor); }
        auto head = cursor;
        for (int i = 0; i < 10 && head != texts.begin(); i++) { head = prev(head); }
        return string(head, cursor);
    }

    string cursorRight(int k) {
        while (cursor != texts.end() && k--) { cursor = next(cursor); }
        auto head = cursor;
        for (int i = 0; i < 10 && head != texts.begin(); i++) { head = prev(head); }
        return string(head, cursor);
    }
};
class MyFoodRatings {
public:
    unordered_map<string, vector<pair<string, int>>> foodmap;
    MyFoodRatings(vector<string> &foods, vector<string> &cuisines, vector<int> &ratings) {
        for (int i = 0; i < cuisines.size(); i++) {
            foodmap[cuisines[i]].push_back({foods[i], ratings[i]});
        }
    }

    void changeRating(string food, int newRating) {
        for (auto &s : foodmap) {
            for (int i = 0; i < s.second.size(); i++) {
                if (s.second[i].first == food) {
                    s.second[i].second = newRating;
                    break;
                }
            }
        }
    }

    string highestRated(string cuisine) {
        if (foodmap.find(cuisine) == foodmap.end()) return ""; // 如果菜系不存在，返回空字符串

        int maxRating = -1;
        string res = "";

        for (const auto &pair : foodmap[cuisine]) {
            if (pair.second > maxRating || (pair.second == maxRating && pair.first < res)) {
                maxRating = pair.second;
                res = pair.first;
            }
        }

        return res;
    }
};
class Solution1422 {
public:
    int maxScore(string s) {
        int score = s[0] == '0' ? 1 : 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == '1') score++;
        }
        int maxScore = score;
        for (int i = 1; i < s.size() - 1; i++) {
            if (s[i] == '0') {
                score++;
                maxScore = max(score, maxScore);
            }
            if (s[i] == '1') score--;
        }
        return score;
    }
};
class Solution852 {
public:
    int peakIndexInMountainArray(vector<int> &arr) {
        int left = 0, right = arr.size() - 2;
        int ans = -1;
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (arr[middle] > arr[middle + 1]) {
                right = middle - 1;
                ans = middle;
            }
            else { left = middle + 1; }
        }
        return ans;
    }
};
class Solution2586 {
public:
    bool yy(string &s) {
        int count = 0;
        for (auto yy : {'a', 'e', 'i', 'o', 'u'}) {
            if (s[0] == yy) { count++; }
            if (s[s.size() - 1] == yy) { count++; }
            if (count == 2) return true;
        }
        return false;
    }
    int vowelStrings(vector<string> &words, int left, int right) {
        int count = 0;
        for (int i = left; i <= right; i++) {
            if (yy(words[i])) count++;
        }
        return count;
    }
};
class Solution503 {
public:
    vector<int> nextGreaterElements(vector<int> &nums) {
        stack<int> st;
        vector<int> res(nums.size(), -1);
        int n = nums.size();
        for (int i = 0; i < 2 * n; i++) {
            if (!st.empty() && nums[st.top()] < nums[i % n]) {
                res[st.top()] = nums[i % n];
                st.pop();
            }
            st.push(i % n);
        }
        return res;
    }
};
class Solution {
    bool check(const string &s, int start, int end) {
        int left = start, right = end;
        while (left <= right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }

public:
    vector<vector<string>> res;
    vector<string> path;
    void back(string &s, int start) {
        if (start >= s.size()) {
            res.push_back(path);
            return;
        }
        for (int i = start; i < s.size(); i++) {
            if (check(s, start, i)) {
                path.push_back(string(s.begin() + start, s.begin() + i + 1));
                back(s, i + 1);
                path.pop_back();
            }
        }
    };
    vector<vector<string>> partition(string s) {
        back(s, 0);
        return res;
    }
};
int main() {}
