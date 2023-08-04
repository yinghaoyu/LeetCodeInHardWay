#include <functional>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 递归
  int uniquePathsIII(vector<vector<int>> &grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    int si = 0;
    int sj = 0;
    int total = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 0)
        {
          total++;
        }
        else if (grid[i][j] == 1)
        {
          total++;
          si = i;
          sj = j;
        }
      }
    }
    vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    function<int(int, int, int)> dfs = [&](int i, int j, int rest)
    {
      if (grid[i][j] == 2)
      {
        return rest == 0 ? 1 : 0;
      }
      int t = grid[i][j];
      int ans = 0;
      grid[i][j] = -1;
      for (auto& dir : dirs)
      {
        int ni = i + dir[0];
        int nj = j + dir[1];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && (grid[ni][nj] == 0 || grid[ni][nj] == 2))
        {
          ans += dfs(ni, nj, rest - 1);
        }
      }
      grid[i][j] = t;
      return ans;
    };
    return dfs(si, sj, total);
  }
};

void test()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}};
  vector<vector<int>> g2 = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 2}};
  vector<vector<int>> g3 = {{0, 1}, {2, 0}};
  EXPECT_EQ_INT(2, s.uniquePathsIII(g1));
  EXPECT_EQ_INT(4, s.uniquePathsIII(g2));
  EXPECT_EQ_INT(0, s.uniquePathsIII(g3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
