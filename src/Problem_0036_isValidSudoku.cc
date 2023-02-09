#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isValidSudoku(vector<vector<char>> &board)
  {
    // 第i行，第j个数是否出现
    bool row[9][10] = {false};
    // 第i列，第j个数是否出现
    bool colum[9][10] = {false};
    // 第i个bucket，第j个数是否出现
    bool bucket[9][10] = {false};
    int n = board.size();
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (board[i][j] != '.')
        {
          int num = board[i][j] - '0';
          // 二维数组转一维数组
          int bid = 3 * (i / 3) + j / 3;
          if (row[i][num] || colum[j][num] || bucket[bid][num])
          {
            return false;
          }
          row[i][num] = true;
          colum[j][num] = true;
          bucket[bid][num] = true;
        }
      }
    }
    return true;
  }
};

void testIsValidSudoku()
{
  Solution s;

  vector<vector<char>> b1 = {
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  vector<vector<char>> b2 = {{'8', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                             {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                             {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                             {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                             {'.', '.', '.', '.', '8', '.', '.', '7', '9'}

  };
  EXPECT_TRUE(s.isValidSudoku(b1));
  EXPECT_FALSE(s.isValidSudoku(b2));
  EXPECT_SUMMARY;
}

int main()
{
  testIsValidSudoku();
  return 0;
}
