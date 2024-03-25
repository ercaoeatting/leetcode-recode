#include <iostream>
#include <vector>

using namespace std;

void pack(int index, int bagweight) {
    vector<int> weight(index, 0); // 存储每件物品所占空间
    vector<int> value(index, 0);  // 存储每件物品价值
    for (int i = 0; i < index; ++i) { cin >> weight[i]; }
    for (int j = 0; j < index; ++j) { cin >> value[j]; }
    vector<vector<int>> dp(index, vector<int>(bagweight + 1, 0));
    for (int j = weight[0]; j <= bagweight; j++) dp[0][j] = value[0];
    for (int i = 1; i < weight.size(); i++) {
        for (int j = 1; j <= bagweight; j++) {
            if (j < weight[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]); // 核心转移公式
        }
    }
    cout << dp[index - 1][bagweight];
    ;
}

int main() {
    int index, bagweight;
    while (cin >> index >> bagweight) { pack(index, bagweight); }
}