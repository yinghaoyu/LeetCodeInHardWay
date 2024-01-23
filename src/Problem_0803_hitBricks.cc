#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> ans(hits.size());
    if (n == 1)
    {
      return ans;
    }
    for (auto& hit : hits)
    {
      grid[hit[0]][hit[1]]--;
    }
    for (int i = 0; i < m; i++)
    {
      dfs(grid, n, m, 0, i);
    }
    for (int i = hits.size() - 1, row, col; i >= 0; i--)
    {
      row = hits[i][0];
      col = hits[i][1];
      grid[row][col]++;
      if (worth(grid, n, m, row, col))
      {
        ans[i] = dfs(grid, n, m, row, col) - 1;
      }
    }
    return ans;
  }

  // 从(i,j)格子出发，遇到1就感染成2
  // 统计新增了几个2！
  int dfs(vector<vector<int>>& grid, int n, int m, int i, int j)
  {
    if (i < 0 || i == n || j < 0 || j == m || grid[i][j] != 1)
    {
      return 0;
    }
    grid[i][j] = 2;
    return 1 + dfs(grid, n, m, i + 1, j) + dfs(grid, n, m, i, j + 1) + dfs(grid, n, m, i - 1, j) +
           dfs(grid, n, m, i, j - 1);
  }

  bool worth(vector<vector<int>>& grid, int n, int m, int i, int j)
  {
    return grid[i][j] == 1 &&
           (i == 0 || (i > 0 && grid[i - 1][j] == 2) || (i < n - 1 && grid[i + 1][j] == 2) ||
            (j > 0 && grid[i][j - 1] == 2) || (j < m - 1 && grid[i][j + 1] == 2));
  }
};

void test()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 0, 0, 0}, {1, 1, 1, 0}};
  vector<vector<int>> h1 = {{1, 0}};
  vector<vector<int>> g2 = {{1, 0, 0, 0}, {1, 1, 0, 0}};
  vector<vector<int>> h2 = {{1, 1}, {1, 0}};
  vector<int> o1 = {2};
  vector<int> o2 = {0, 0};
  EXPECT_TRUE(o1 == s.hitBricks(g1, h1));
  EXPECT_TRUE(o2 == s.hitBricks(g2, h2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
