#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
// 二分查找 704
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int middle = left + (left + right) / 2;
        if (nums[middle] < target) { left = middle + 1; }
        else if (nums[middle] > target) { right = middle - 1; }
        else { return middle; }
    }
    return -1;
}

class solution_serch {
public:
    // 左闭右闭区间
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int middle = left + (left + right) / 2;
            if (nums[middle] > target)
                right = middle - 1;
            else if (nums[middle] < target)
                left = middle + 1;
            else
                return middle;
        }
        return -1;
    }
    // 左闭右开区间
    int search2(vector<int>& nums, int target) {
        int left = 0, right = nums.size(), middle;
        while (left < right) {
            middle = (left + right) / 2;
            if (nums[middle] > target)
                right = middle;
            else if (nums[middle] < target)
                left = middle + 1;
            else
                return middle;
        }
        return -1;
    }
};
// 移除元素 27
class solution_removeElement {
public:
    // 暴力遍历，时间复杂度O(n^2) 空间复杂度O(1)
    int removeElement1(vector<int>& nums, int val) {
        int size = nums.size();
        for (int ii = 0; ii < size; ii++) {
            if (nums[ii] == val) {
                for (int jj = ii + 1; jj < size; jj++) nums[jj - 1] = nums[jj];
                ii--;
                size--;
            }
        }
        return size;
    }
    // 双指针法，时间复杂度O(n) 空间复杂度O(1)
    int removeElement2(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
        }
        return slow;
    }
    // 相向双指针法，基于元素顺序可以改变的题目描述改变了元素相对位置，确保了移动最少元素
    int removeElement3(vector<int>& nums, int val) {
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;
        while (leftIndex <= rightIndex) {
            // 找左边等于val的元素
            while (leftIndex <= rightIndex && nums[leftIndex] != val) { ++leftIndex; }
            // 找右边不等于val的元素
            while (leftIndex <= rightIndex && nums[rightIndex] == val) { --rightIndex; }
            // 将右边不等于val的元素覆盖左边等于val的元素
            if (leftIndex < rightIndex) { nums[leftIndex++] = nums[rightIndex--]; }
        }
        return leftIndex; // leftIndex一定指向了最终数组末尾的下一个元素
    }
};
// 有序数组的平方
class solution_nums2 {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int k = nums.size() - 1;
        vector<int> res(k + 1, 0);
        for (int left = 0, right = k; left <= right;) {
            int squareLeft = nums[left] * nums[left];
            int squareRight = nums[right] * nums[right];
            if (squareLeft < squareRight) {
                res[k--] = squareRight;
                right--;
            }
            else {
                res[k--] = squareLeft;
                left++;
            }
        }
        return res;
    }
};
class solution_minSubArrayLen {
public:
    // 暴力遍历
    int minSubArrayLen0(int s, vector<int>& nums) {
        int res = INT32_MAX;
        int subSum = 0; // 子序列和
        int subLen = 0; // 子序列长度
        for (int i = 0; i < nums.size(); i++) {
            subSum = 0;
            for (int j = i; j < nums.size(); j++) {
                subSum += nums[j];
                if (subSum > s) {
                    subLen = j - i + 1;
                    res = subLen < res ? subLen : res;
                    break;
                }
            }
        }
        return res == INT32_MAX ? 0 : res;
    }
    // 滑动窗口
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT32_MAX;
        int subSum = 0; // 子序列和
        int subLen = 0; // 子序列长度
        int l = 0;      // 滑动窗口起始位置
        for (int r = 0; r < nums.size(); r++) {
            subSum += nums[r];
            while (subSum >= s) {
                subLen = r - l + 1;
                res = res < subLen ? res : subLen;
                subSum -= nums[l++]; // 精华所在
            }
        }
        return res == INT32_MAX ? 0 : res;
    }
    // 找子串和小于s的最大长度
    int maxSubArrayLen(int s, vector<int>& nums) {
        int res = 0;
        int subSum = 0;
        int subLen = 0;
        int left = 0;
        int right = 0;
        while (right <= nums.size()) {
            subSum += nums[right];
            while (subSum > s) { subSum -= nums[left++]; }
            subLen = right - left + 1;
            res = res > subLen ? res : subLen;
            right++;
        }
        return res == 0 ? 0 : res;
    }
};
class solution_Matrix {
public:
    vector<vector<int>> generateMatrix(int n) {
        // 左闭右闭区间
        vector<vector<int>> res(n, vector<int>(n, 0));
        int left = 0, right = n - 1, top = 0, bottom = n - 1, num = 1;
        while (left <= right && top <= bottom) {
            // 从左到右
            for (int i = left; i <= right; i++) res[top][i] = num++;
            top++;
            // 从上到下
            for (int i = top; i <= bottom; i++) res[i][right] = num++;
            right--;
            // 从右到左
            for (int i = right; i >= left; i--) res[bottom][i] = num++;
            bottom--;
            // 从下到上
            for (int i = bottom; i >= top; i--) res[i][left] = num++;
            left++;
        }
        return res;
    }
    vector<vector<int>> generateMatrix2(int n) {
        // 左闭右开区间
        vector<vector<int>> res(n, vector<int>(n, 0));
        int left = 0, right = n - 1, top = 0, bottom = n - 1, num = 1;
        while (left < right && top < bottom) {
            // 从左到右
            for (int i = left; i < right; i++) res[top][i] = num++;
            top++;
            // 从上到下
            for (int i = top; i < bottom; i++) res[i][right] = num++;
            right--;
            // 从右到左
            for (int i = right; i > left; i--) res[bottom][i] = num++;
            bottom--;
            // 从下到上
            for (int i = bottom; i > top; i--) res[i][left] = num++;
            left++;
        }
        return res;
    }
    vector<vector<int>> generateMatrix3(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0)); // 使用vector定义一个二维数组
        int startx = 0, starty = 0;                    // 定义每循环一个圈的起始位置
        int loop =
            n /
            2; // 每个圈循环几次，例如n为奇数3，那么loop = 1 只是循环一圈，矩阵中间的值需要单独处理
        int mid =
            n / 2; // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
        int count = 1; // 用来给矩阵中每一个空格赋值
        int offset = 1; // 需要控制每一条边遍历的长度，每次循环右边界收缩一位
        int i, j;
        while (loop--) {
            i = startx;
            j = starty;

            // 下面开始的四个for就是模拟转了一圈
            // 模拟填充上行从左到右(左闭右开)
            for (j = starty; j < n - offset; j++) { res[startx][j] = count++; }
            // 模拟填充右列从上到下(左闭右开)
            for (i = startx; i < n - offset; i++) { res[i][j] = count++; }
            // 模拟填充下行从右到左(左闭右开)
            for (; j > starty; j--) { res[i][j] = count++; }
            // 模拟填充左列从下到上(左闭右开)
            for (; i > startx; i--) { res[i][j] = count++; }

            // 第二圈开始的时候，起始位置要各自加1， 例如：第一圈起始位置是(0,
            // 0)，第二圈起始位置是(1, 1)
            startx++;
            starty++;

            // offset 控制每一圈里每一条边遍历的长度
            offset += 1;
        }

        // 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
        if (n % 2) { res[mid][mid] = count; }
        return res;
    }
    // 54
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res;
        int left = 0, right = n - 1, top = 0, bottom = m - 1;
        while (left <= right && top <= bottom) {
            // 从左到右
            for (int i = left; i <= right; i++) res.push_back(matrix[top][i]);
            top++;
            // 从上到下
            for (int i = top; i <= bottom; i++) res.push_back(matrix[i][right]);
            right--;
            // 从右到左
            if (top <= bottom) { // 这个和下面的判断在m!=n时是必须的
                for (int i = right; i >= left; i--) res.push_back(matrix[bottom][i]);
                bottom--;
            }

            // 从下到上
            if (left <= right) {
                for (int i = bottom; i >= top; i--) res.push_back(matrix[i][left]);
                left++;
            }
        }
        return res;
    }
};
class solution_leetcode34 { // 在排序数组中查找元素的第一个和最后一个位置
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = serachFirst(nums, target);
        int last = serachLast(nums, target);
        return {first, last};
    }

private:
    int serachFirst(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == nums[mid]) {
                if (mid > 0 && nums[mid - 1] == nums[mid]) { right = mid - 1; }
                else
                    return mid;
            }
            else if (target < nums[mid]) { right = mid - 1; }
            else { left = mid + 1; }
        }
        return -1;
    }
    int serachLast(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == nums[mid]) {
                if (mid != nums.size() - 1 && nums[mid + 1] == nums[mid]) { left = mid + 1; }
                else
                    return mid;
            }
            else if (target < nums[mid]) { right = mid - 1; }
            else { left = mid + 1; }
        }
        return -1;
    }
};
class s367 {
    //     给你一个正整数 num 。如果 num 是一个完全平方数，则返回 true ，否则返回 false 。
    // 完全平方数 是一个可以写成某个整数的平方的整数。换句话说，它可以写成某个整数和自身的乘积。
    // 不能使用任何内置的库函数，如  sqrt 。
public:
    bool isPerfectSquare(int num) {
        if (num == 1) return 1;
        int left = 1, right = num - 1;
        int mid;
        while (left <= right) {
            mid = left + ((right - left) >> 1);
            if (num / mid == mid)
                break;
            else if (num / mid > mid)
                left = mid + 1;
            else if (num / mid < mid)
                right = mid - 1;
        }
        return mid * mid == num;
    }
};
class s26
// 给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次
// ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致然后返回 nums 中唯一元素的个数。
// 考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：
// 更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums
// 的其余元素与 nums 的大小不重要。 返回 k 。
{
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 1, fast = 1, k = nums.size();
        for (; fast < nums.size(); fast++) {
            if (nums[fast] != nums[fast - 1]) { nums[slow++] = nums[fast]; }
            else
                k--;
        }
        return k;
    }
};
class s27
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
{
public:
    void moveZeroes(vector<int>& nums) {
        for (int slow, fast = 0; fast < nums.size(); fast++)
            if (nums[fast]) swap(nums[fast], nums[slow++]);
    }
};
class s844 {
public:
    // 给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回 true 。
    // # 代表退格字符。注意：如果对空文本输入退格字符，文本继续为空。
    bool backspaceCompare(string& s, string& t) {
        stringDeal(s);
        stringDeal(t);
        return s == t;
    }

private:
    void stringDeal(string& s) {
        int slow = 0, fast = 0, size_s = s.size(), k = s.size();
        for (; fast < k; fast++) {
            size_s = size_s < 0 ? 0 : size_s;
            slow = slow < 0 ? 0 : slow;
            {
                if (s[fast] != '#')
                    s[slow++] = s[fast];
                else if (slow > 0) {
                    slow--;
                    size_s--;
                    size_s--;
                }
                else
                    size_s--;
            }
        }
        s.resize(size_s);
    }
};
class s904_fruitBasket {
    // 找至多包含两种元素的最长子串，返回其长度
public:
    int totalFruit(vector<int>& fruits) {
        int left = 0, right = 0, res = 0;
        unordered_map<int, int> species;
        while (right < fruits.size()) {
            ++species[fruits[right]];
            while (species.size() > 2) {
                int currentFruit = fruits[left];
                --species[currentFruit];
                if (species[currentFruit] == 0) species.erase(currentFruit);
                left++;
            }
            res = res > (right - left + 1) ? res : (right - left + 1);
            right++;
        }
        return res;
    }
};
class s76_myFirstHard {
public:
    string minWindow(string s, string t) {
        unordered_map<int, int> res, need;
        for (auto& i : t) { ++need[i]; }
        // count为res满足数量要求的数量
        int left = 0, right = 0, count = 0, len = INT32_MAX, start = 0;
        while (right < s.size()) {
            // 判断是否满足条件
            if (need.find(s[right]) != need.end()) {
                // 应将窗口扩充
                ++res[s[right]];
                if (res[s[right]] == need[s[right]]) count++;
            }
            while (count == need.size()) {
                // 更新结果
                if (len > right - left + 1) {
                    start = left;
                    len = right - left + 1;
                }
                // 最大程度地压缩left
                // 如果s left恰好在窗口内，那么需要处理结果哈希表
                if (need.find(s[left]) != need.end()) {
                    if (res[s[left]] == need[s[left]]) --count;
                    --res[s[left]];
                }
                left++;
            }
            ++right;
        }
        return len == INT32_MAX ? "" : s.substr(start, len);
    }
};

int main() {
    string s = "sadsafback", t = "ack";
    string a = s76_myFirstHard().minWindow(s, t);
}