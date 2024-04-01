// 一维dp数组实现
#include <iostream>
#include <vector>
using namespace std;
void deal(int M, int bagweight) {
    vector<int> weight(M, 0);
    vector<int> value(M, 0);
    for (int i = 0; i < M; i++) { cin >> weight[i]; }
    for (int j = 0; j < M; j++) { cin >> value[j]; }
    vector<int> dp(bagweight + 1, 0);
    for (int i = 0; i < M; i++) {
        for (int j = bagweight; j >= weight[0]; j--) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    std::cout << dp[bagweight] << std::endl;
}
int main() {
    int M, N;
    while (cin >> M >> N) { deal(M, N); }
}
