#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int deleteGreatestValue(vector<vector<int>> &grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; i++)
    {
      std::sort(grid[i].begin(), grid[i].end());
    }
    int ans = 0;
    for (int j = m - 1; j >= 0; j--)
    {
      int max = INT32_MIN;
      for (int i = 0; i < n; i++)
      {
        max = std::max(max, grid[i][j]);
      }
      ans += max;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 2, 4}, {3, 3, 1}};
  vector<vector<int>> g2 = {{10}};
  EXPECT_EQ_INT(8, s.deleteGreatestValue(g1));
  EXPECT_EQ_INT(10, s.deleteGreatestValue(g2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
