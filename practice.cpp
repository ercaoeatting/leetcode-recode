
#include <algorithm>
#include <cstdint>
#include <deque>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> result;
    queue<TreeNode *, deque<TreeNode *>> queue;
    if (root != nullptr) { queue.push(root); }
    while (!queue.empty()) {
        vector<int> tmp;
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            tmp.push_back(queue.front()->val);
            if (queue.front()->left) queue.push(queue.front()->left);
            if (queue.front()->right) queue.push(queue.front()->right);
        }
        result.push_back(tmp);
    }
    return result;
}