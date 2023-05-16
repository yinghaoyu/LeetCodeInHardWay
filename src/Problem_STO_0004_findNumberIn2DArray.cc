#include <vector>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
      if(matrix.size() == 0 || matrix[0].size() == 0)
      {
        return false;
      }
      int row = 0;
      int col = matrix[0].size() - 1;
      while(row < matrix.size() && col >= 0)
      {
        if(matrix[row][col] > target)
        {
          col--;
        }
        else if(matrix[row][col] < target)
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

void testFindNumberIn2DArray()
{
  Solution s;
  vector<vector<int>> m1 = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
  EXPECT_TRUE(s.findNumberIn2DArray(m1, 5));
  EXPECT_FALSE(s.findNumberIn2DArray(m1, 20));
  EXPECT_SUMMARY;
}

int main()
{
  testFindNumberIn2DArray();
  return 0;
}
