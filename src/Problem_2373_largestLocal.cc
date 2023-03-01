#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<int>> largestLocal(vector<vector<int>> &grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> ans(n - 2, vector<int>(m - 2));
    for (int i = 0; i < n - 2; i++)
    {
      for (int j = 0; j < m - 2; j++)
      {
        ans[i][j] = max(grid, i, j, i + 2, j + 2);
      }
    }
    return ans;
  }

  int max(vector<vector<int>> &grid, int r1, int c1, int r2, int c2)
  {
    int ans = 0;
    for (int i = r1; i <= r2; i++)
    {
      for (int j = c1; j <= c2; j++)
      {
        ans = std::max(ans, grid[i][j]);
      }
    }
    return ans;
  }
};

void testLargestLocal()
{
  Solution s;
  vector<vector<int>> g1 = {{9, 9, 8, 1}, {5, 6, 2, 6}, {8, 2, 6, 4}, {6, 2, 2, 2}};
  vector<vector<int>> o1 = {{9, 9}, {8, 6}};
  vector<vector<int>> g2 = {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 2, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}};
  vector<vector<int>> o2 = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
  EXPECT_TRUE(o1 == s.largestLocal(g1));
  EXPECT_TRUE(o2 == s.largestLocal(g2));
  EXPECT_SUMMARY;
}

int main()
{
  testLargestLocal();
  return 0;
}
