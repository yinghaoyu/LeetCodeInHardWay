#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool checkXMatrix(vector<vector<int>> &grid)
  {
    int n = grid.size();
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i == j || i + j == n - 1)
        {
          if (grid[i][j] == 0)
          {
            return false;
          }
        }
        else
        {
          if (grid[i][j] != 0)
          {
            return false;
          }
        }
      }
    }
    return true;
  }
};

void testCheckXMatrix()
{
  Solution s;
  vector<vector<int>> g1 = {{2, 0, 0, 1}, {0, 3, 1, 0}, {0, 5, 2, 0}, {4, 0, 0, 2}};
  vector<vector<int>> g2 = {{5, 7, 0}, {0, 3, 1}, {0, 5, 0}};
  EXPECT_TRUE(s.checkXMatrix(g1));
  EXPECT_FALSE(s.checkXMatrix(g2));
  EXPECT_SUMMARY;
}

int main()
{
  testCheckXMatrix();
  return 0;
}
