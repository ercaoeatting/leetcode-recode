
#include <iostream>
#include <vector>
using namespace std;
int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
int n, m;
void dfs(vector<vector<int>> &grid, vector<vector<int>> &visited, int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nxtx = x + dir[i][0];
        int nxty = y + dir[i][1];
        if (nxtx < 0 || nxty < 0 || nxtx >= n || nxty >= m) continue;
        if (visited[nxtx][nxty] || !grid[nxtx][nxty]) continue;
        visited[nxtx][nxty] = 1;
        dfs(grid, visited, nxtx, nxty);
    }
}

int main(int argc, char *argv[]) {
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    vector<vector<int>> visited(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && grid[i][j]) {
                visited[i][j] = 1;
                ans++;
                dfs(grid, visited, i, j);
            }
        }
    }
    cout << ans;
}