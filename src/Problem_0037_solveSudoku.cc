#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void initMaps(vector<vector<char>> &board, vector<vector<bool>> &row, vector<vector<bool>> &colum, vector<vector<bool>> &bucket)
  {
    int n = board.size();
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (board[i][j] != '.')
        {
          int num = board[i][j] - '0';
          int bid = 3 * (i / 3) + j / 3;
          row[i][num] = true;
          colum[j][num] = true;
          bucket[bid][num] = true;
        }
      }
    }
  }

  bool process(vector<vector<char>> &board, int i, int j, vector<vector<bool>> &row, vector<vector<bool>> &colum, vector<vector<bool>>& bucket)
  {
    if (i == board.size())
    {
      return true;
    }
    int nexti = j == 8 ? i + 1 : i;
    int nextj = j == 8 ? 0 : j + 1;
    if (board[i][j] != '.')
    {
      return process(board, nexti, nextj, row, colum, bucket);
    }
    else
    {
      int bid = 3 * (i / 3) + j / 3;
      for (int x = 1; x < 10; x++)
      {
        if (!row[i][x] && !colum[j][x] && !bucket[bid][x])
        {
          row[i][x] = true;
          colum[j][x] = true;
          bucket[bid][x] = true;
          board[i][j] = x + '0';
          if (process(board, nexti, nextj, row, colum, bucket))
          {
            return true;
          }
          row[i][x] = false;
          colum[j][x] = false;
          bucket[bid][x] = false;
          board[i][j] = '.';
        }
      }
      return false;
    }
  }

  void solveSudoku(vector<vector<char>> &board)
  {
    vector<vector<bool>> row(9, vector<bool>(10, false));
    vector<vector<bool>> colum(9, vector<bool>(10, false));
    vector<vector<bool>> bucket(9, vector<bool>(10, false));
    initMaps(board, row, colum, bucket);
    process(board, 0, 0, row, colum, bucket);
  }
};

void testSolveSudoku()
{
  Solution s;
  vector<vector<char>> b1 = {
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  vector<vector<char>> b2 = {
      {'5', '3', '4', '6', '7', '8', '9', '1', '2'}, {'6', '7', '2', '1', '9', '5', '3', '4', '8'}, {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
      {'8', '5', '9', '7', '6', '1', '4', '2', '3'}, {'4', '2', '6', '8', '5', '3', '7', '9', '1'}, {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
      {'9', '6', '1', '5', '3', '7', '2', '8', '4'}, {'2', '8', '7', '4', '1', '9', '6', '3', '5'}, {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};
  s.solveSudoku(b1);
  EXPECT_TRUE(b2 == b1);
  EXPECT_SUMMARY;
}

int main()
{
  testSolveSudoku();
  return 0;
}
