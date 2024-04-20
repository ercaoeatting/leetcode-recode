#include <list>
#include <unordered_set>
#include <string>
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

int main() {}