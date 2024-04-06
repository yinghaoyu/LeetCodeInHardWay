#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool canWalk(vector<vector<int>>& grid, int i, int j)
  {
    return i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size();
  }

  int f(vector<vector<int>>& grid, int i, int j)
  {
    if (!canWalk(grid, i, j))
    {
      return INT32_MAX;
    }
    if (i == grid.size() - 1 && j == grid[0].size() - 1)
    {
      return grid[i][j];
    }
    int distance = INT32_MAX;
    if (canWalk(grid, i + 1, j))
    {
      distance = std::min(distance, f(grid, i + 1, j));
    }
    if (canWalk(grid, i, j + 1))
    {
      distance = std::min(distance, f(grid, i, j + 1));
    }
    return distance == INT32_MAX ? INT32_MAX : distance + grid[i][j];
  }

  // 递归，超时
  int minPathSum1(vector<vector<int>>& grid) { return f(grid, 0, 0); }

  int minPathSum2(vector<vector<int>>& grid)
  {
    int N = grid.size();
    int M = grid[0].size();
    vector<vector<int>> dp(N + 1, vector<int>(M + 1, INT32_MAX));
    dp[N - 1][M - 1] = grid[N - 1][M - 1];
    for (int i = N - 1; i >= 0; i--)
    {
      for (int j = M - 1; j >= 0; j--)
      {
        int distance = std::min(dp[i + 1][j], dp[i][j + 1]);
        if (distance != INT32_MAX)
        {
          dp[i][j] = distance + grid[i][j];
        }
      }
    }
    return dp[0][0];
  }

  // dp空间压缩
  // 仔细观察可以发现，由于二维dp的填充方式是从右下角开始，从右到左，从下到上
  // 所以我们可以设置一个一维数组进行滚动刷新，而不需要浪费一个二维数组的额外空间
  int minPathSum3(vector<vector<int>>& grid)
  {
    int N = grid.size();
    int M = grid[0].size();
    if (N == 0 || M == 0)
    {
      return 0;
    }
    // 其实应该是一张二维表，但是用了空间压缩技巧
    vector<int> dp(M);
    // dp数组变成，想象中二维表的第0行数据
    // m : 3 2 1 6 3 5 6 12
    dp[0] = grid[0][0];
    for (int i = 1; i < M; i++)
    {
      dp[i] = dp[i - 1] + grid[0][i];
    }
    for (int i = 1; i < N; i++)
    {
      // dp此时是想象中二维表的第i-1行数据
      // 想更新成，想象中二维表的第i行数据
      // dp[0]
      dp[0] = dp[0] + grid[i][0];
      for (int j = 1; j < M; j++)
      {
        dp[j] = std::min(dp[j - 1], dp[j]) + grid[i][j];
      }
    }
    return dp[M - 1];
  }
};

void testMinPathSum()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
  vector<vector<int>> g2 = {{1, 2, 3}, {4, 5, 6}};
  EXPECT_EQ_INT(7, s.minPathSum1(g1));
  EXPECT_EQ_INT(12, s.minPathSum1(g2));
  EXPECT_EQ_INT(7, s.minPathSum2(g1));
  EXPECT_EQ_INT(12, s.minPathSum2(g2));
  EXPECT_EQ_INT(7, s.minPathSum3(g1));
  EXPECT_EQ_INT(12, s.minPathSum3(g2));
  EXPECT_SUMMARY;
}

int main()
{
  testMinPathSum();
  return 0;
}
