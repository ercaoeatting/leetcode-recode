#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int ans = 0;
    int dir[4][2] = {0, -1, 0, 1, 1, 0, -1, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != 1) continue;
            ans += 4;
            grid[i][j] = 2;
            for (int k = 0; k < 4; k++) {
                int nx = i + dir[k][0];
                int ny = j + dir[k][1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
                }
            }
        }
    }
}