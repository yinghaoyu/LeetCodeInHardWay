#include <memory.h>
#include <tuple>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minimumMoves(vector<vector<int>> &grid)
  {
    int n = grid.size();
    static constexpr int DIRS[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    bool vis[n][n][2];
    memset(vis, 0, sizeof(vis));
    vis[0][0][0] = true;
    vector<tuple<int, int, int>> q = {{0, 0, 0}};  // 初始位置
    for (int step = 1; !q.empty(); ++step)
    {
      vector<tuple<int, int, int>> nxt;
      for (const auto &[X, Y, S] : q)
      {
        for (const auto &d : DIRS)
        {
          int x = X + d[0], y = Y + d[1], s = S ^ d[2];
          int x2 = x + s, y2 = y + (s ^ 1);  // 蛇头
          if (x2 < n && y2 < n && !vis[x][y][s] && grid[x][y] == 0 && grid[x2][y2] == 0 && (d[2] == 0 || grid[x + 1][y + 1] == 0))
          {
            if (x == n - 1 && y == n - 2)
              return step;  // 此时蛇头一定在 (n-1,n-1)
            vis[x][y][s] = true;
            nxt.emplace_back(x, y, s);
          }
        }
      }
      q = move(nxt);
    }
    return -1;
  }
};

void testMinimumMoves()
{
  Solution s;
  vector<vector<int>> g1 = {{0, 0, 0, 0, 0, 1}, {1, 1, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 1}, {0, 0, 1, 0, 1, 0}, {0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 0}};
  vector<vector<int>> g2 = {{0, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 1}, {1, 1, 0, 0, 0, 1}, {1, 1, 1, 0, 0, 1}, {1, 1, 1, 0, 0, 1}, {1, 1, 1, 0, 0, 0}};
  EXPECT_EQ_INT(11, s.minimumMoves(g1));
  EXPECT_EQ_INT(9, s.minimumMoves(g2));
  EXPECT_SUMMARY;
}

int main()
{
  testMinimumMoves();
  return 0;
}
