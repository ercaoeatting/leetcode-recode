#include <algorithm>
#include <vector>
using namespace std;
// 分发饼干
class Solution {
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