#include <unordered_set>
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