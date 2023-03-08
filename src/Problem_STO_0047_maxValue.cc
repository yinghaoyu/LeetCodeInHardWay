#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int process(vector<vector<int>> &grid, int i, int j)
  {
    if (i < 0 || j < 0)
    {
      return 0;
    }
    return std::max(process(grid, i, j - 1), process(grid, i - 1, j)) + grid[i][j];
  }

  int maxValue(vector<vector<int>> &grid) { return process(grid, grid.size() - 1, grid[0].size() - 1); }

  int maxValue1(vector<vector<int>> &grid)
  {
    int N = grid.size();
    int M = grid[0].size();
    vector<vector<int>> dp(N, vector<int>(M));
    dp[N - 1][M - 1] = grid[N - 1][M - 1];
    for (int j = M - 2; j >= 0; j--)
    {
      dp[N - 1][j] = dp[N - 1][j + 1] + grid[N - 1][j];
    }
    for (int i = N - 2; i >= 0; i--)
    {
      dp[i][M - 1] = dp[i + 1][M - 1] + grid[i][M - 1];
    }
    for (int i = N - 2; i >= 0; i--)
    {
      for (int j = M - 2; j >= 0; j--)
      {
        dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]) + grid[i][j];
      }
    }
    return dp[0][0];
  }

  int maxValue2(vector<vector<int>> &grid)
  {
    int M = grid.size(), N = grid[0].size();
    vector<vector<int>> dp(M, vector<int>(N));
    for (int i = 0; i < M; ++i)
    {
      for (int j = 0; j < N; ++j)
      {
        if (i > 0)
        {
          dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
        if (j > 0)
        {
          dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
        dp[i][j] += grid[i][j];
      }
    }
    return dp[M - 1][N - 1];
  }

  // 空间优化
  int maxValue3(vector<vector<int>> &grid)
  {
    int M = grid.size(), N = grid[0].size();
    vector<vector<int>> dp(2, vector<int>(N));
    for (int i = 0; i < M; ++i)
    {
      int pos = i & 1;
      for (int j = 0; j < N; ++j)
      {
        if (i > 0)
        {
          dp[pos][j] = max(dp[pos][j], dp[1 - pos][j]);
        }
        if (j > 0)
        {
          dp[pos][j] = max(dp[pos][j], dp[pos][j - 1]);
        }
        dp[pos][j] += grid[i][j];
      }
    }
    return dp[(M - 1) & 1][N - 1];
  }
};

void testMaxValue()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
  EXPECT_EQ_INT(12, s.maxValue(n1));
  EXPECT_EQ_INT(12, s.maxValue1(n1));
  EXPECT_EQ_INT(12, s.maxValue2(n1));
  EXPECT_EQ_INT(12, s.maxValue3(n1));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxValue();
  return 0;
}
