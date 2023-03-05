#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 两次二分
  bool searchMatrix1(vector<vector<int>> &matrix, int target)
  {
    int M = matrix.size();
    int N = matrix[0].size();
    int l = 0;
    int r = M - 1;
    int row = -1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (matrix[m][0] <= target)
      {
        row = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    if (row == -1)
    {
      return false;
    }
    l = 0;
    r = N - 1;
    int col = -1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (matrix[row][m] <= target)
      {
        col = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return col != -1 && matrix[row][col] == target;
  }

  // 二维数组转一维数组
  bool searchMatrix2(vector<vector<int>> &matrix, int target)
  {
    int M = matrix.size();
    int N = matrix[0].size();
    int l = 0;
    int r = M * N - 1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      int x = matrix[m / N][m % N];
      if (x < target)
      {
        l = m + 1;
      }
      else if (x > target)
      {
        r = m - 1;
      }
      else
      {
        return true;
      }
    }
    return false;
  }

  bool searchMatrix3(vector<vector<int>> &matrix, int target)
  {
    int N = matrix.size();
    int M = matrix[0].size();
    int row = 0;
    int col = M - 1;
    while (row < N && col >= 0)
    {
      if (matrix[row][col] > target)
      {
        col--;
      }
      else if (matrix[row][col] < target)
      {
        row++;
      }
      else
      {
        return true;
      }
    }
    return false;
  }
};

void testSearchMatrix()
{
  Solution s;
  vector<vector<int>> n = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  EXPECT_TRUE(s.searchMatrix1(n, 3));
  EXPECT_FALSE(s.searchMatrix1(n, 13));
  EXPECT_TRUE(s.searchMatrix2(n, 3));
  EXPECT_FALSE(s.searchMatrix2(n, 13));
  EXPECT_TRUE(s.searchMatrix3(n, 3));
  EXPECT_FALSE(s.searchMatrix3(n, 13));
  EXPECT_SUMMARY;
}

int main()
{
  testSearchMatrix();
  return 0;
}
