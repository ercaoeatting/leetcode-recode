#include <algorithm>
#include <vector>
using namespace std;
// 分发饼干
class lc455 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int count = 0;
        for (int i = g.size() - 1, j = s.size() - 1; i >= 0; i--) {
            if (j >= 0 && s[j] >= g[i]) {
                count++;
                j--;
            }
        }
        return count;
    }
};
// 摆动序列
class lc376 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() == 1) return 1;

        int count = 1;
        int predif = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            int curdif = nums[i + 1] - nums[i];
            if ((predif >= 0 && curdif < 0) || (predif <= 0 && curdif > 0)) {
                count++;
                predif = curdif;
            }
        }
        return count;
    }
};
