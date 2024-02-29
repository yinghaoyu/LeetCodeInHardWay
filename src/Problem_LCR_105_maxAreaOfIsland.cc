#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/max-area-of-island/
// @sa Problem_0695_maxAreaOfIsland.cc
class Solution
{
 public:
  static constexpr int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  int dfs(vector<vector<int>>& grid, int x, int y)
  {
    if (x < 0 || y < 0 || x == grid.size() || y == grid[0].size() || grid[x][y] != 1)
    {
      return 0;
    }
    grid[x][y] = 0;
    int ans = 1;
    for (int i = 0; i < 4; i++)
    {
      int nextx = x + direction[i][0];
      int nexty = y + direction[i][1];
      ans += dfs(grid, nextx, nexty);
    }
    return ans;
  }

  // dfs
  int maxAreaOfIsland(vector<vector<int>>& grid)
  {
    int ans = 0;
    for (int i = 0; i < grid.size(); i++)
    {
      for (int j = 0; j < grid[0].size(); j++)
      {
        ans = std::max(ans, dfs(grid, i, j));
      }
    }
    return ans;
  }
};
