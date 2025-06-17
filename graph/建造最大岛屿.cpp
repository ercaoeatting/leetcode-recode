#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
int area;
int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
void dfs(vector<vector<int>> &grid, int x, int y, int mark) {
    if (grid[x][y] != 1) return;
    grid[x][y] = mark;
    area++;
    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size()) {
            continue;
        }
        dfs(grid, nx, ny, mark);
    }
}
int main(int argc, char *argv[]) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    unordered_map<int, int> island_area; // mark -> area
    int mark = 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != 1) continue;
            dfs(grid, i, j, mark);
            island_area[mark] = area;
            area = 0;
            mark++;
        }
    }
    bool isAll = true;
    unordered_set<int> visited;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            area = 1;
            if (grid[i][j] != 0) continue;
            isAll = false;
            visited.clear();
            for (int k = 0; k < 4; k++) {
                int nx = i + dir[k][0];
                int ny = j + dir[k][1];
                if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size()) {
                    continue;
                }
                if (visited.count(island_area[grid[nx][ny]])) continue;
                visited.insert(island_area[grid[nx][ny]]);
                area += island_area[grid[nx][ny]];
            }
            ans = max(area, ans);
        }
    }
    ans = isAll ? m * n : ans;
    cout << ans;
}