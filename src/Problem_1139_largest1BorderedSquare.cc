#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 模拟
  int largest1BorderedSquare1(vector<vector<int>> &grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    int len = std::min(n, m);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        for (int k = len - 1; k >= 0; k--)
        {
          if (i + k < n && j + k < m && isSquare(grid, i, j, i + k, j + k))
          {
            ans = std::max(ans, (k + 1) * (k + 1));
            break;
          }
        }
      }
    }
    return ans;
  }

  bool isSquare(vector<vector<int>> &grid, int uR, int uC, int dR, int dC)
  {
    int curR = uR;
    int curC = uC;
    while (curC != dC)
    {
      if (grid[uR][curC] != 1)
      {
        return false;
      }
      curC++;
    }
    while (curR != dR)
    {
      if (grid[curR][dC] != 1)
      {
        return false;
      }
      curR++;
    }
    while (curC != uC)
    {
      if (grid[dR][curC] != 1)
      {
        return false;
      }
      curC--;
    }
    while (curR != uR)
    {
      if (grid[curR][uC] != 1)
      {
        return false;
      }
      curR--;
    }
    return grid[uR][uC] == 1;
  }

  // https://leetcode.cn/problems/largest-1-bordered-square/solution/java-dong-tai-gui-hua-by-resolmi/
  int largest1BorderedSquare2(vector<vector<int>> &grid)
  {
    int m = grid.size();
    int n = grid[0].size();
    // dp[i][j][0]: i,j左边连续的1的个数
    // dp[i][j][1]: i,j上边连续的1的个数
    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(2)));
    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (grid[i - 1][j - 1] == 1)
        {
          dp[i][j][0] = 1 + dp[i][j - 1][0];
          dp[i][j][1] = 1 + dp[i - 1][j][1];
        }
      }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        //最短的那条边不一定是合法的边长，如果该边长不合法就需要缩减边长，直到找到合法的
        for (int side = std::min(dp[i][j][0], dp[i][j][1]); side >= 1; side--)
        {
          if (dp[i][j - side + 1][1] >= side && dp[i - side + 1][j][0] >= side)
          {
            ans = std::max(ans, side);
            break;  //更短的就没必要考虑了
          }
        }
      }
    }
    return ans * ans;
  }
};

void testLargest1BorderedSquare()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  vector<vector<int>> g2 = {{1, 1, 0, 0}};
  vector<vector<int>> g3 = {{1, 1, 1}, {1, 1, 0}, {0, 0, 0}};
  vector<vector<int>> g4 = {{0, 0, 0, 1}};
  vector<vector<int>> g5 = {{0}};
  EXPECT_EQ_INT(9, s.largest1BorderedSquare1(g1));
  EXPECT_EQ_INT(1, s.largest1BorderedSquare1(g2));
  EXPECT_EQ_INT(4, s.largest1BorderedSquare1(g3));
  EXPECT_EQ_INT(1, s.largest1BorderedSquare1(g4));
  EXPECT_EQ_INT(0, s.largest1BorderedSquare1(g5));
  EXPECT_EQ_INT(9, s.largest1BorderedSquare2(g1));
  EXPECT_EQ_INT(1, s.largest1BorderedSquare2(g2));
  EXPECT_EQ_INT(4, s.largest1BorderedSquare2(g3));
  EXPECT_EQ_INT(1, s.largest1BorderedSquare2(g4));
  EXPECT_EQ_INT(0, s.largest1BorderedSquare2(g5));
  EXPECT_SUMMARY;
}

int main()
{
  testLargest1BorderedSquare();
  return 0;
}
