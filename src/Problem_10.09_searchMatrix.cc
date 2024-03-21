#include <vector>

using namespace std;

class Solution
{
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target)
  {
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
      // 防止下面取 m 的时候越界
      return false;
    }
    int n = matrix.size();
    int m = matrix[0].size();
    int row = 0;
    int col = m - 1;
    while (row < n && col >= 0)
    {
      if (matrix[row][col] == target)
      {
        return true;
      }
      else if (matrix[row][col] < target)
      {
        row++;
      }
      else
      {
        col--;
      }
    }
    return false;
  }
};
