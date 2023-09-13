#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 第一时间想到的解
  bool checkValidGrid(vector<vector<int>> &grid)
  {
    if (grid[0][0] != 0)
    {
      return false;
    }
    const vector<vector<int>> dir = {{1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}};
    int startx = 0;
    int starty = 0;
    int step = 0;
    int n = grid.size();
    vector<vector<bool>> seen(n, vector<bool>(n));
    queue<std::pair<int, int>> q;
    q.push({startx, starty});
    while (!q.empty())
    {
      auto [x, y] = q.front();
      seen[x][y] = true;
      q.pop();
      for (int i = 0; i < 8; i++)
      {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || n <= nextx || nexty < 0 || n <= nexty)
        {
          continue;
        }
        if (!seen[nextx][nexty] && grid[nextx][nexty] == step + 1)
        {
          q.push({nextx, nexty});
          step++;
        }
      }
    }
    return step + 1 == n * n;
  }

  // 最优解
  bool best(vector<vector<int>> &grid)
  {
    if (grid[0][0] != 0)
    {
      // 不符合从左上角开始
      return false;
    }
    int n = grid.size();
    vector<vector<int>> steps(n * n, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        // grid[i][j] 一定是连续的且在区间 [0, n * n) 内
        steps[grid[i][j]] = {i, j};
      }
    }
    for (int i = 1; i < steps.size(); i++)
    {
      // 检查相邻的步数是否是 日型
      int dx = std::abs(steps[i][0] - steps[i - 1][0]);
      int dy = std::abs(steps[i][1] - steps[i - 1][1]);
      if (dx * dy != 2)
      {
        return false;
      }
    }
    return true;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> g1 = {{0, 11, 16, 5, 20}, {17, 4, 19, 10, 15}, {12, 1, 8, 21, 6}, {3, 18, 23, 14, 9}, {24, 13, 2, 7, 22}};
  vector<vector<int>> g2 = {{0, 3, 6}, {5, 8, 1}, {2, 7, 4}};
  EXPECT_TRUE(s.checkValidGrid(g1));
  EXPECT_FALSE(s.checkValidGrid(g2));
  EXPECT_TRUE(s.best(g1));
  EXPECT_FALSE(s.best(g2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
