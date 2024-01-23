#include <vector>

#include "UnitTest.h"

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  int largestIsland(vector<vector<int>>& grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    int id = 2;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 1)
        {
          dfs(grid, n, m, i, j, id++);
        }
      }
    }
    vector<int> size(id);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] > 1)
        {
          ans = std::max(ans, ++size[grid[i][j]]);
        }
      }
    }
    // 讨论所有的0，变成1，能带来的最大岛的大小
    vector<bool> visited(id);
    int up, down, left, right, merge;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 0)
        {
          up = i > 0 ? grid[i - 1][j] : 0;
          down = i + 1 < n ? grid[i + 1][j] : 0;
          left = j > 0 ? grid[i][j - 1] : 0;
          right = j + 1 < m ? grid[i][j + 1] : 0;
          visited[up] = true;
          merge = 1 + size[up];
          if (!visited[down])
          {
            merge += size[down];
            visited[down] = true;
          }
          if (!visited[left])
          {
            merge += size[left];
            visited[left] = true;
          }
          if (!visited[right])
          {
            merge += size[right];
            visited[right] = true;
          }
          ans = std::max(ans, merge);
          visited[up] = false;
          visited[down] = false;
          visited[left] = false;
          visited[right] = false;
        }
      }
    }
    return ans;
  }

  void dfs(vector<vector<int>>& grid, int n, int m, int i, int j, int id)
  {
    if (i < 0 || i == n || j < 0 || j == m || grid[i][j] != 1)
    {
      return;
    }
    grid[i][j] = id;
    dfs(grid, n, m, i - 1, j, id);
    dfs(grid, n, m, i + 1, j, id);
    dfs(grid, n, m, i, j - 1, id);
    dfs(grid, n, m, i, j + 1, id);
  }
};

void test()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 0}, {0, 1}};
  vector<vector<int>> g2 = {{1, 1}, {1, 0}};
  vector<vector<int>> g3 = {{1, 1}, {1, 1}};
  EXPECT_EQ_INT(3, s.largestIsland(g1));
  EXPECT_EQ_INT(4, s.largestIsland(g2));
  EXPECT_EQ_INT(4, s.largestIsland(g3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
