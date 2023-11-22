#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  int process(vector<vector<int>>& grid, vector<vector<int>>& moveCost, int x, int y, vector<vector<int>>& c)
  {
    if (x == grid.size() - 1)
    {
      return grid[x][y];
    }
    if (c[x][y] != INT32_MAX)
    {
      return c[x][y];
    }
    int cost = INT32_MAX;
    int cur = grid[x][y];
    for (int i = 0; i < moveCost[0].size(); i++)
    {
      cost = std::min(cost, cur + moveCost[cur][i] + process(grid, moveCost, x + 1, i, c));
    }
    c[x][y] = cost;
    return cost;
  }

  // 记忆化搜索
  int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost)
  {
    int ans = INT32_MAX;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < m; i++)
    {
      vector<vector<int>> c(n, vector<int>(m, INT32_MAX));
      ans = std::min(ans, process(grid, moveCost, 0, i, c));
    }
    return ans;
  }

  // 记忆化搜索改dp
  int dp(vector<vector<int>>& grid, vector<vector<int>>& moveCost)
  {
    int m = grid.size();
    int n = grid[0].size();
    // 空间优化，下一行只依赖上一行的结果
    vector<vector<int>> dp(2, vector<int>(n));
    // base case
    dp[0] = grid[0];
    int cur = 0;
    // 从第 1 行开始
    for (int i = 1; i < m; i++)
    {
      int next = 1 - cur;
      // 枚举所有列
      for (int j = 0; j < n; j++)
      {
        dp[next][j] = INT32_MAX;
        for (int k = 0; k < n; k++)
        {
          dp[next][j] = std::min(dp[next][j], dp[cur][k] + moveCost[grid[i - 1][k]][j] + grid[i][j]);
        }
      }
      cur = next;
    }
    // 可以从第 1 行任意节点开始，因此取最小值
    return *min_element(dp[cur].begin(), dp[cur].end());
  }
};

int main()
{
  return 0;
}
