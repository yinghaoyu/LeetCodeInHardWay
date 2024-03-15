#include <functional>
#include <vector>

using namespace std;

class Solution
{
  vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid)
  {
    vector<vector<int>> ans;  // 记录路径
    if (obstacleGrid.size() == 0 || obstacleGrid[0].size() == 0)
    {
      return ans;
    }
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));  // 记录访问过的节点
    function<bool(int, int)> dfs = [&](int x, int y)
    {
      if (x >= m || y >= n || obstacleGrid[x][y] == 1 || visited[x][y])
      {
        return false;
      }
      if (x == m - 1 && y == n - 1)
      {
        ans.push_back({x, y});
        return true;
      }
      visited[x][y] = true;
      ans.push_back({x, y});
      if (dfs(x + 1, y) || dfs(x, y + 1))
      {
        return true;
      }
      ans.pop_back();
      // vis[x][y] = false; 核心是不要写这行
      return false;
    };
    dfs(0, 0);
    return ans;
  }
};
