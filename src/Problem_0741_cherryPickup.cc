#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  int N;
  int M;

 public:
  // 原题意：一个人从(0, 0)走到(N-1, M-1)，再从(N-1, M-1)返回到(0, 0)
  // 可以将往、返，拆成两个人同时往下走一步
  // 由于两个人的步数一定相同，所以第二个人的y2 = x1 + y1 - x2，简化了参数
  int cherryPickup(vector<vector<int>> &grid)
  {
    N = grid.size();
    M = grid[0].size();
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(N, INT32_MIN)));
    int ans = procss(grid, 0, 0, 0, dp);
    return ans < 0 ? 0 : ans;
  }

  int procss(vector<vector<int>> &grid, int x1, int y1, int x2, vector<vector<vector<int>>> &dp)
  {
    // 由于一直是+1操作，所以不需要考虑下界
    if (x1 >= N || y1 >= M || x2 >= N || x1 + y1 - x2 >= N)
    {
      return INT32_MIN;
    }
    if (dp[x1][y1][x2] != INT32_MIN)
    {
      return dp[x1][y1][x2];
    }
    if (x1 == N - 1 && y1 == M - 1)
    {
      // 两个人都到达终点
      dp[x1][y1][x2] = grid[x1][y1];
      return dp[x1][y1][x2];
    }
    int next = INT32_MIN;
    next = std::max(next, procss(grid, x1 + 1, y1, x2 + 1, dp));
    next = std::max(next, procss(grid, x1 + 1, y1, x2, dp));
    next = std::max(next, procss(grid, x1, y1 + 1, x2 + 1, dp));
    next = std::max(next, procss(grid, x1, y1 + 1, x2, dp));
    if (grid[x1][y1] == -1 || grid[x2][x1 + y1 - x2] == -1 || next == INT32_MIN)
    {
      // 有一个人走到荆棘或者越界，说明这种尝试无效
      dp[x1][y1][x2] = INT32_MIN;
      return dp[x1][y1][x2];
    }
    if (x1 == x2)
    {
      // 当两个人走到一个点时，只算一份樱桃
      dp[x1][y1][x2] = grid[x1][y1] + next;
      return dp[x1][y1][x2];
    }
    // 走到不同点则算两份樱桃
    dp[x1][y1][x2] = grid[x1][y1] + grid[x2][x1 + y1 - x2] + next;
    return dp[x1][y1][x2];
  }

  // 递归改dp
  int dp(vector<vector<int>> &grid)
  {
    N = grid.size();
    M = grid[0].size();
    vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(M + 1, vector<int>(N + 1, INT32_MIN)));
    for (int x1 = N - 1; x1 >= 0; x1--)
    {
      for (int y1 = M - 1; y1 >= 0; y1--)
      {
        for (int x2 = N - 1; x2 >= 0; x2--)
        {
          if(x1 + y1 - x2 < 0 ||  x1 + y1 - x2 >= N)
          {
            // 注意：跟递归不同，这里要加这个边界条件
            continue;
          }
          int next = INT32_MIN;
          next = std::max(next, dp[x1 + 1][y1][x2 + 1]);
          next = std::max(next, dp[x1 + 1][y1][x2]);
          next = std::max(next, dp[x1][y1 + 1][x2 + 1]);
          next = std::max(next, dp[x1][y1 + 1][x2]);
          if (x1 == N - 1 && y1 == M - 1)
          {
            dp[x1][y1][x2] = grid[x1][y1];
          }
          else if (grid[x1][y1] == -1 || grid[x2][x1 + y1 - x2] == -1 || next == INT32_MIN)
          {
            dp[x1][y1][x2] = INT32_MIN;
          }
          else if (x1 == x2)
          {
            dp[x1][y1][x2] = grid[x1][y1] + next;
          }
          else
          {
            dp[x1][y1][x2] = grid[x1][y1] + grid[x2][x1 + y1 - x2] + next;
          }
        }
      }
    }
    return dp[0][0][0] == INT32_MIN ? 0 : dp[0][0][0];
  }
};

void testCherryPickup()
{
  Solution s;
  vector<vector<int>> n1 = {{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
  vector<vector<int>> n2 = {{1, 1, -1}, {1, -1, 1}, {-1, 1, 1}};
  vector<vector<int>> n3 = {{1, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 0, 0},
                            {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 1}};
  EXPECT_EQ_INT(5, s.cherryPickup(n1));
  EXPECT_EQ_INT(0, s.cherryPickup(n2));
  EXPECT_EQ_INT(15, s.cherryPickup(n3));
  EXPECT_EQ_INT(5, s.dp(n1));
  EXPECT_EQ_INT(0, s.dp(n2));
  EXPECT_EQ_INT(15, s.dp(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testCherryPickup();
  return 0;
}
