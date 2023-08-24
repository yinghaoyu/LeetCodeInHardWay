#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countServers(vector<vector<int>> &grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> row(n);
    vector<int> col(m);
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 1)
        {
          row[i]++;
          col[j]++;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 1 && (row[i] > 1 || col[j] > 1))
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
  vector<vector<int>> g1 = {{1, 0}, {0, 1}};
  vector<vector<int>> g2 = {{1, 0}, {1, 1}};
  vector<vector<int>> g3 = {{1, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  EXPECT_EQ_INT(0, s.countServers(g1));
  EXPECT_EQ_INT(3, s.countServers(g2));
  EXPECT_EQ_INT(4, s.countServers(g3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
