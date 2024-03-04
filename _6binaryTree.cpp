
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    void traversal(TreeNode *cur, vector<int> &vec) {
        if (cur == nullptr) return;
        vec.push_back(cur->val);
        traversal(cur->left, vec);
        traversal(cur->right, vec);
    }
};
// 前序遍历 递归法
class lc144 {
    void traversal(TreeNode *cur, vector<int> &vec) {
        if (cur == nullptr) return;
        vec.push_back(cur->val);
        traversal(cur->left, vec);
        traversal(cur->right, vec);
    }

public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        traversal(root, res);
        return res;
    }
};
// 前序遍历 迭代法
class lc144_dd {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        stack<TreeNode *> st;
        if (root == nullptr) return vector<int>{};
        st.push(root);
        while (!st.empty()) {
            TreeNode *node = st.top();
            st.pop();
            res.push_back(node->val);
            if (node->right) { st.push(node->right); }
            if (node->left) { st.push(node->left); }
        }
        return res;
    }
};
// 中序遍历
class inorder {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        stack<TreeNode *> st;
        TreeNode *cur = root;
        while (cur != nullptr || !st.empty()) {
            if (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            else {
                cur = st.top();
                st.pop();
                result.push_back(cur->val);
                cur = cur->right;
            }
        }
        return result;
    }
};
// 后序遍历 中左右->中右左->左右中
class post {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == nullptr) return result;
        st.push(root);
        while (!st.empty()) {
            TreeNode *node = st.top();
            st.pop();
            result.push_back(node->val);
            if (node->left)
                st.push(node->left); // 相对于前序遍历，这更改一下入栈顺序 （空节点不入栈）
            if (node->right) st.push(node->right); // 空节点不入栈
        }
        reverse(result.begin(), result.end()); // 将结果反转之后就是左右中的顺序了
        return result;
    }
};
// 二叉树的统一迭代法  使用空指针进行标记
class inorder2 {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        stack<TreeNode *> st;
        if (root != nullptr) st.push(root);
        while (!st.empty()) {
            TreeNode *node = st.top();
            if (node != nullptr) {
                st.pop(); // 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
                if (node->right) st.push(node->right); // 添加右节点（空节点不入栈）
                st.push(node);                         // 添加中节点
                st.push(nullptr); // 中节点访问过，但是还没有处理，加入空节点做为标记。
                if (node->left) st.push(node->left); // 添加左节点（空节点不入栈）
            }
            else {        // 只有遇到空节点的时候，才将下一个节点放进结果集
                st.pop(); // 将空节点弹出
                node = st.top(); // 重新取出栈中元素
                st.pop();
                result.push_back(node->val); // 加入到结果集
            }
        }
        return result;
    }
};
class lc102 {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        queue<TreeNode *> queue;
        vector<vector<int>> result;
        vector<int> tmp;
        if (root != nullptr) { queue.push(root); }
        while (!queue.empty()) {
            tmp = vector<int>{};
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode *cur = queue.front();
                queue.pop();
                tmp.push_back(cur->val);
                if (cur->left) queue.push(cur->left);
                if (cur->right) queue.push(cur->right);
            }
            result.push_back(tmp);
        }
        // LC107 reverse(result.begin(), result.end());
        return result;
    }
};
class lc199 {
public:
    vector<int> rightSideView(TreeNode *root) {
        queue<TreeNode *> queue;
        vector<int> result;
        vector<int> tmp;
        if (root != nullptr) { queue.push(root); }
        while (!queue.empty()) {
            int size = queue.size();
            tmp = vector<int>{};
            for (int i = 0; i < size; i++) {
                TreeNode *cur = queue.front();
                queue.pop();
                tmp.push_back(cur->val);
                if (cur->left) queue.push(cur->left);
                if (cur->right) queue.push(cur->right);
            }
            result.push_back(tmp[size - 1]);
        }
        return result;
    }
};
class lc637 {
public:
    vector<double> averageOfLevels(TreeNode *root) {
        queue<TreeNode *> queue;
        vector<double> result;
        if (root != nullptr) { queue.push(root); }
        while (!queue.empty()) {
            int size = queue.size();
            vector<int> tmp{};
            double sumOfLevels = 0;
            for (int i = 0; i < size; i++) {
                TreeNode *cur = queue.front();
                queue.pop();
                tmp.push_back(cur->val);
                if (cur->left) queue.push(cur->left);
                if (cur->right) queue.push(cur->right);
            }
            for (auto it = tmp.begin(); it != tmp.end(); it++) { sumOfLevels += *it; }
            result.push_back(sumOfLevels / tmp.size());
        }
        return result;
    }
};
class Node {
public:
    int val;
    vector<Node *> children;
    Node() {}
    Node(int _val) { val = _val; }
    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};
class lc429 {
public:
    vector<vector<int>> levelOrder(Node *root) {
        queue<Node *> queue;
        vector<vector<int>> result;
        vector<int> tmp;
        if (root != nullptr) { queue.push(root); }
        while (!queue.empty()) {
            tmp = vector<int>{};
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                Node *cur = queue.front();
                queue.pop();
                tmp.push_back(cur->val);
                for (int i = 0; i < cur->children.size(); i++) {
                    if (cur->children[i]) { queue.push(cur->children[i]); }
                }
            }
            result.push_back(tmp);
        }
        return result;
    }
};
class lc515 {
public:
    vector<int> largestValues(TreeNode *root) {
        queue<TreeNode *> queue;
        vector<int> result;
        if (root != nullptr) { queue.push(root); }
        while (!queue.empty()) {
            int size = queue.size();
            vector<int> tmp{};
            int maxValue = INT32_MIN;
            for (int i = 0; i < size; i++) {
                TreeNode *cur = queue.front();
                queue.pop();
                tmp.push_back(cur->val);
                if (cur->left) queue.push(cur->left);
                if (cur->right) queue.push(cur->right);
            }
            for (auto it = tmp.begin(); it != tmp.end(); it++) {
                maxValue = (maxValue < *it) ? *it : maxValue;
            }
            result.push_back(maxValue);
        }
        return result;
    }
};

// 求最大深度按逻辑
class lc104_recursion {
public:
    int result;
    void getDepth(TreeNode *node, int depth) {
        result = depth > result ? depth : result; // 中

        if (node->left == NULL && node->right == NULL) return;

        if (node->left) { // 左
            depth++;      // 深度+1
            getDepth(node->left, depth);
            depth--; // 回溯，深度-1
        }
        if (node->right) { // 右
            depth++;       // 深度+1
            getDepth(node->right, depth);
            depth--; // 回溯，深度-1
        }
        return;
    }
    int maxDepth(TreeNode *root) {
        result = 0;
        if (root == NULL) return result;
        getDepth(root, 1);
        return result;
    }
};
class lc101 {
public:
    bool compareNode(TreeNode *left, TreeNode *right) {
        if (left == nullptr && right != nullptr)
            return false;
        else if (left != nullptr && right == nullptr)
            return false;
        else if (left == nullptr && right == nullptr)
            return true;
        else if (left->val != right->val)
            return false;
        return compareNode(left->left, right->right) && compareNode(left->right, right->left);
    }
    bool isSymmetric(TreeNode *root) {
        if (root == nullptr) return true;
        return compareNode(root->left, root->right);
    }
};
class lc110 {
public:
    int balance(TreeNode *node) {
        if (node == nullptr) return 0;
        int leftTree = balance(node->left);
        if (leftTree == -1) return -1;
        int rightTree = balance(node->right);
        if (rightTree == -1) return -1;
        if (abs(leftTree - rightTree) > 1) { return -1; }
        else { return max(leftTree, rightTree) + 1; }
    }
    bool isBalanced(TreeNode *root) {
        if (root == nullptr) return true;
        return (balance(root) != -1) ? true : false;
    }
};
class lc257 {
public:
    void traversal(TreeNode *cur, vector<int> &path, vector<string> &result) {
        path.push_back(cur->val);
        if (cur->left == nullptr && cur->right == nullptr) {
            string resultIn;
            for (int i = 0; i < path.size() - 1; i++) {
                resultIn += to_string(path[i]);
                resultIn += "->";
            }
            resultIn += to_string(path[path.size() - 1]);
            result.push_back(resultIn);
        }
        if (cur->left) {
            traversal(cur->left, path, result);
            path.pop_back();
        }
        if (cur->right) {
            traversal(cur->right, path, result);
            path.pop_back();
        }
    }
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> result;
        vector<int> path;
        if (root == NULL) return result;
        traversal(root, path, result);
        return result;
    }
};

class lc404 {
public:
    int sumOfLeftLeaves1(TreeNode *root) {
        queue<TreeNode *> que;
        if (root != nullptr) { que.push(root); }
        int result = 0;
        while (!que.empty()) {
            TreeNode *node = que.front();
            que.pop();
            if (node->left != nullptr && node->left->left == nullptr &&
                node->left->right == nullptr) {
                result += node->left->val;
            }
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        return result;
    }
    int sumOfLeftLeaves(TreeNode *root) {
        if (root == nullptr) return 0;
        int resultLeft = 0;
        int resultRight = 0;
        resultLeft = sumOfLeftLeaves(root->left);
        if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
            resultLeft = root->left->val;
        }
        resultRight = sumOfLeftLeaves(root->right);
        return resultLeft + resultRight;
    }
};

class lc513 {
public:
    int maxDepth = INT_MIN;
    int result;
    void traversal(TreeNode *root, int depth) {
        if (root->left == nullptr && root->right == nullptr) {
            if (depth > maxDepth) {
                maxDepth = depth;
                result = root->val;
            }
        }
        if (root->left) {
            depth++;
            traversal(root->left, depth);
            depth--;
        }
        if (root->right) {
            depth++;
            traversal(root->right, depth);
            depth--;
        }
    }
    int findBottomLeftValue(TreeNode *root) {
        traversal(root, 1);
        return result;
    }
};
class lc112 {
public:
    bool traversal(TreeNode *cur, int count) {
        if (cur->left == nullptr && cur->right == nullptr && count == 0) return true;
        if (cur->left == nullptr && cur->right == nullptr) return false;
        if (cur->left) {
            if (traversal(cur->left, count - cur->left->val)) return true;
        }
        if (cur->right) {
            if (traversal(cur->right, count - cur->right->val)) return true;
        }
        return false;
    }
    bool hasPathSum(TreeNode *root, int targetSum) {
        if (root == nullptr) return false;
        return traversal(root, targetSum - root->val);
    }
};
class lc113 {
public:
    void traversal(TreeNode *cur, int count, vector<vector<int>> &result, vector<int> &path) {
        path.push_back(cur->val);
        if (cur->left == nullptr && cur->right == nullptr && count == 0) { result.push_back(path); }
        if (cur->left == nullptr && cur->right == nullptr) return;
        if (cur->left) {
            traversal(cur->left, count - cur->left->val, result, path);
            path.pop_back();
        }

        if (cur->right) {
            traversal(cur->right, count - cur->right->val, result, path);
            path.pop_back();
        }
    }
    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        vector<vector<int>> result;
        vector<int> path;
        if (root == nullptr) return result;
        traversal(root, targetSum - root->val, result, path);
        return result;
    }
};
class lc106 {
public:
    TreeNode *traversal(vector<int> &inorder, vector<int> &postorder) {
        if (postorder.size() == 0) return nullptr;
        TreeNode *node = new TreeNode(postorder[postorder.size() - 1]);
        if (postorder.size() == 1) return node;
        int cutPos = 0;
        while (true) {
            if (inorder[cutPos++] == postorder[postorder.size() - 1]) break;
        }
        cutPos--;

        vector<int> leftIn = vector<int>(inorder.begin(), inorder.begin() + cutPos);
        vector<int> rightIn = vector<int>(inorder.begin() + cutPos + 1, inorder.end());
        vector<int> leftPost = vector<int>(postorder.begin(), postorder.begin() + leftIn.size());
        vector<int> rightPost = vector<int>(postorder.begin() + leftIn.size(), postorder.end() - 1);

        node->left = traversal(leftIn, leftPost);
        node->right = traversal(rightIn, rightPost);
        return node;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if (inorder.size() == 0) return nullptr;
        return traversal(inorder, postorder);
    }
};
class lc105 {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (preorder.empty()) return nullptr;
        TreeNode *root = new TreeNode(preorder[0]);
        if (preorder.size() == 1) return root;
        int cutPos;
        for (cutPos = 0; cutPos < preorder.size(); cutPos++) {
            if (inorder[cutPos] == preorder[0]) break;
        }
        vector<int> leftin = vector<int>(inorder.begin(), inorder.begin() + cutPos);
        vector<int> rightin = vector<int>(inorder.begin() + cutPos + 1, inorder.end());
        vector<int> leftpre =
            vector<int>(preorder.begin() + 1, preorder.begin() + leftin.size() + 1);
        vector<int> rightpre = vector<int>(preorder.begin() + leftin.size() + 1, preorder.end());
        root->left = buildTree(leftpre, leftin);
        root->right = buildTree(rightpre, rightin);
        return root;
    }
};
class lc654 {
public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        TreeNode *node = new TreeNode(0);
        if (nums.size() == 1) {
            node->val = nums[0];
            return node;
        }
        pair<int, int> max_value_index(INT32_MIN, -1);
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > max_value_index.first) {
                max_value_index.first = nums[i];
                max_value_index.second = i;
            }
        }
        node->val = max_value_index.first;
        if (max_value_index.second > 0) {
            vector<int> leftVec(nums.begin(), nums.begin() + max_value_index.second);
            node->left = constructMaximumBinaryTree(leftVec);
        }
        if (max_value_index.second < nums.size() - 1) {
            vector<int> rightVec(nums.begin() + max_value_index.second + 1, nums.end());
            node->right = constructMaximumBinaryTree(rightVec);
        }
        return node;
    }
};
class lc617 {
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr) return root2;
        if (root2 == nullptr) return root1;

        // Both trees are non-empty; merge them
        // TreeNode *root = new TreeNode(root1->val + root2->val);
        // 原地修改效率高
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }
};
// 二叉搜索树
class lc700 {
public:
    TreeNode *searchBST(TreeNode *root, int val) {
        if (root == nullptr) return nullptr;
        if (root->val == val) return root;
        if (root->val > val) return searchBST(root->left, val);
        if (root->val < val) return searchBST(root->right, val);
        return nullptr;
    }
};
// 二叉搜索树的验证
class lc98 {
public:
    void sortInorder(TreeNode *root, vector<int> &sortvec) {
        if (root == nullptr) return;
        sortInorder(root->left, sortvec);
        sortvec.push_back(root->val);
        sortInorder(root->right, sortvec);
    }
    bool isValidBST(TreeNode *root) {
        vector<int> sortvec;
        sortInorder(root, sortvec);

        for (int i = 0; i < sortvec.size() - 1; i++) {
            if (sortvec[i] >= sortvec[i + 1]) return false;
        }
        return true;
    }
};
// 二叉搜索树的最小绝对差
class lc530 {
public:
    int result = INT_MAX;
    TreeNode *pre = nullptr;

    int getMinimumDifference(TreeNode *root) {
        if (root == nullptr) return result;

        getMinimumDifference(root->left);
        if (pre != nullptr) result = min(result, root->val - pre->val);
        pre = root;
        getMinimumDifference(root->right);
        return result;
    }
};
// 二叉搜索树中的众数
class lc501 {
public:
    vector<int> result;
    TreeNode *pre;
    int count;
    int maxcount;
    lc501() : result(vector<int>()), pre(nullptr), count(0), maxcount(0) {}
    vector<int> findMode(TreeNode *root) {
        if (!root) return result;
        findMode(root->left);
        if (pre == nullptr) { count = 1; }
        else if (pre->val == root->val) { count++; }
        else { count = 1; }
        if (count == maxcount) { result.push_back(root->val); }
        else if (count > maxcount) {
            maxcount = count;
            result.clear();
            result.push_back(root->val);
        }
        findMode(root->right);
        return result;
    }
};
// 二叉树最近公共祖先
class lc236 {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left && right) { return root; }
        else if (left) { return left; }
        else if (right) { return right; }
        else { return nullptr; }
    }
};
// BST最近公共祖先
class lc235 {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root->val > p->val && root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
        else if (root->val < p->val && root->val < q->val) {
            return lowestCommonAncestor(root->right, p, q);
        }
        else
            return root;
    }
};
// 二叉搜索树的插入
// 记得再看看迭代法
class lc701 {
public:
    TreeNode *insertIntoBST(TreeNode *root, int val) {
        if (root == nullptr) // 中
        {
            TreeNode *node = new TreeNode(val);
            return node;
        }
        if (root->val > val) { root->left = insertIntoBST(root->left, val); }        // 左
        else if (root->val < val) { root->right = insertIntoBST(root->right, val); } // 右
        return root;
    }
};

// 删除BST的节点
class lc450 {
public:
    TreeNode *deleteNode(TreeNode *root, int key) {
        if (root == nullptr) return nullptr;
        if (root->val == key) {
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            }
            else if (!root->left) {
                TreeNode *node = root->right;
                delete root;
                return node;
            }
            else if (!root->right) {
                TreeNode *node = root->left;
                delete root;
                return node;
            }
            else {
                TreeNode *rightleave = root->right;
                while (!rightleave->left) { rightleave = rightleave->left; }
                rightleave->left = root->left;
                root->left = nullptr;
                TreeNode *node2 = root->right;
                delete root;
                return node2;
            }
        }
        else if (root->val > key)
            root->left = deleteNode(root->left, key);
        else
            root->right = deleteNode(root->right, key);
        return root;
    }
    TreeNode *solution2(TreeNode *root, int key) {
        if (root == nullptr) return root;
        if (root->val == key) {
            if (root->right == nullptr) { // 这里第二次操作目标值：最终删除的作用
                return root->left;
            }
            TreeNode *cur = root->right;
            while (cur->left) { cur = cur->left; }
            swap(root->val, cur->val); // 这里第一次操作目标值：交换目标值其右子树最左面节点。
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};
// 修剪二叉搜索树
class lc669 {
public:
    TreeNode *trimBST(TreeNode *root, int low, int high) {
        if (!root) return nullptr;
        if (root->val < low) return trimBST(root->right, low, high);
        if (root->val > high) return trimBST(root->left, low, high);
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
};
// 将有序数组转换为二叉搜索树
class lc108 {
public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        TreeNode *node = new TreeNode(0);
        if (nums.size() == 1) {
            node->val = nums[0];
            return node;
        }
        int seg = nums.size() / 2;
        vector<int> left(nums.begin(), nums.begin() + seg);
        vector<int> right(nums.begin() + seg + 1, nums.end());
        TreeNode *root = new TreeNode(nums[seg]);
        if (left.size() > 0) root->left = sortedArrayToBST(left);
        if (right.size() > 0) root->right = sortedArrayToBST(right);
        return root;
    }
};
// 二叉树转为累加
class lc538 {
public:
    int pre = 0;
    void traversal(TreeNode *cur) {
        if (cur == nullptr) return;
        traversal(cur->right);
        cur->val += pre;
        pre = cur->val;
        traversal(cur->left);
    }
    TreeNode *convertBST(TreeNode *root) {
        traversal(root);
        return root;
    }
};
int main() {
    vector<int> a{3, 9, 20, 15, 7};
    vector<int> b{9, 3, 15, 20, 7};
}