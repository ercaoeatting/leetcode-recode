#include <unordered_set>
#include <string>
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

class Solution {
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
int main() {
    string s = "string";
    string t = Solution().finalString(s);
}