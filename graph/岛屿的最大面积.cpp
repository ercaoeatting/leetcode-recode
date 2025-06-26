
#include <iostream>
#include <vector>
using namespace std;
int count;
int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
void dfs(vector<vector<int>> &grid, vector<vector<int>> &visited, int x,
         int y) {
  if (visited[x][y] || !grid[x][y]) return;
  count++;
  visited[x][y] = 1;
  for (int i = 0; i < 4; i++) {
    int nx = x + dir[i][0];
    int ny = y + dir[i][1];
    if (nx < 0 || ny < 0 || nx >= visited.size() || ny >= visited[0].size())
      continue;
    dfs(grid, visited, nx, ny);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> grid(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
    }
  }
  vector<vector<int>> visited(n, vector<int>(m, 0));
  int res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (visited[i][j] || !grid[i][j]) continue;
      count = 0;
      dfs(grid, visited, i, j);
      res = max(count, res);
    }
  }
  cout << res;
}