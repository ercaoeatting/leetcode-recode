#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
int area;
int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
void dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y, int mark) {
    if (visited[x][y] || grid[x][y] == 0) return;
    visited[x][y] = true;
    grid[x][y] = mark;
    area++;
    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size()) continue;
        dfs(grid, visited, nx, ny, mark);
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
    vector<vector<bool>> visited(n, vector<bool>(m, false)); // 标记访问过的点

    unordered_map<int, int> umap; // mark -> area;
    int mark = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visited[i][j]) continue;
            area = 0;
            dfs(grid, visited, i, j, mark);
            mark++;
            umap[mark] = area;
        }
    }
    int result = 0;                 // 记录最后结果
    unordered_set<int> visitedGrid; // 标记访问过的岛屿
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            area = 1;            // 记录连接之后的岛屿数量
            visitedGrid.clear(); // 每次使用时，清空
            if (grid[i][j] == 0) {
                for (int k = 0; k < 4; k++) {
                    int neari = i + dir[k][1]; // 计算相邻坐标
                    int nearj = j + dir[k][0];
                    if (neari < 0 || neari >= n || nearj < 0 || nearj >= m) continue;
                    if (visitedGrid.count(grid[neari][nearj])) continue; // 添加过的岛屿不要重复添加
                    // 把相邻四面的岛屿数量加起来
                    area += umap[grid[neari][nearj]];
                    visitedGrid.insert(grid[neari][nearj]); // 标记该岛屿已经添加过
                }
            }
            result = max(result, area);
        }
    }
    cout << result << endl;
}