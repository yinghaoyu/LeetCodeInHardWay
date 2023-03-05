#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
   // 和74题不同
   // 这题没有确保「每行的第一个整数大于前一行的最后一个整数」，因此不能用两次二分!!!
   // 从右上角看，这个矩阵相当于二叉搜索树
  bool searchMatrix(vector<vector<int>> &matrix, int target)
  {
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
      return false;
    }
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
  vector<vector<int>> n = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
  EXPECT_TRUE(s.searchMatrix(n, 5));
  EXPECT_FALSE(s.searchMatrix(n, 20));
  EXPECT_SUMMARY;
}

int main()
{
  testSearchMatrix();
  return 0;
}
