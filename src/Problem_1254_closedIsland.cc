#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int bfs(vector<vector<int>> &grid)
  {
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int m = grid.size();
    int n = grid[0].size();
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (grid[i][j] == 0)
        {
          queue<std::pair<int, int>> q;
          grid[i][j] = 1;
          bool closed = true;
          q.push({i, j});
          while (!q.empty())
          {
            auto [cx, cy] = q.front();
            q.pop();
            if (cx == 0 || cy == 0 || cx == m - 1 || cy == n - 1)
            {
              closed = false;
            }
            for (int k = 0; k < 4; k++)
            {
              int nx = cx + dirs[k][0];
              int ny = cy + dirs[k][1];
              if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 0)
              {
                grid[nx][ny] = 1;
                q.push({nx, ny});
              }
            }
          }
          if (closed)
          {
            ans++;
          }
        }
      }
    }
    return ans;
  }

  int dfs(vector<vector<int>> &grid)
  {
    int ans = 0;
    int m = grid.size();
    int n = grid[0].size();
    std::function<bool(int, int)> f = [&](int x, int y) -> bool
    {
      if (x < 0 || y < 0 || x >= m || y >= n)
      {
        return false;
      }
      if (grid[x][y] != 0)
      {
        return true;
      }
      grid[x][y] = 1;
      bool p1 = f(x - 1, y);
      bool p2 = f(x + 1, y);
      bool p3 = f(x, y - 1);
      bool p4 = f(x, y + 1);
      return p1 && p2 && p3 && p4;
    };

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (grid[i][j] == 0 && f(i, j))
        {
          ans++;
        }
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 1, 1, 1, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1, 1, 0}, {1, 0, 1, 0, 1, 1, 1, 0}, {1, 0, 0, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 0}};
  vector<vector<int>> g2 = {{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 1, 0}};
  vector<vector<int>> g3 = {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 1, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1},
                            {1, 0, 1, 1, 1, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1}};
  auto g4 = g1;
  auto g5 = g2;
  auto g6 = g3;
  EXPECT_EQ_INT(2, s.bfs(g1));
  EXPECT_EQ_INT(1, s.bfs(g2));
  EXPECT_EQ_INT(2, s.bfs(g3));

  EXPECT_EQ_INT(2, s.dfs(g4));
  EXPECT_EQ_INT(1, s.dfs(g5));
  EXPECT_EQ_INT(2, s.dfs(g6));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
