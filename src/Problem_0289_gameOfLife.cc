#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void gameOfLife(vector<vector<int>> &board)
  {
    int N = board.size();
    int M = board[0].size();
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        int nb = neighbors(board, i, j);
        if (nb == 3 || (board[i][j] == 1 && nb == 2))
        {
          set(board, i, j);
        }
      }
    }
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        board[i][j] = get(board, i, j);
      }
    }
  }

  int neighbors(vector<vector<int>> &board, int i, int j)
  {
    int count = 0;
    count += ok(board, i - 1, j - 1) ? 1 : 0;
    count += ok(board, i - 1, j) ? 1 : 0;
    count += ok(board, i - 1, j + 1) ? 1 : 0;
    count += ok(board, i, j - 1) ? 1 : 0;
    count += ok(board, i, j + 1) ? 1 : 0;
    count += ok(board, i + 1, j - 1) ? 1 : 0;
    count += ok(board, i + 1, j) ? 1 : 0;
    count += ok(board, i + 1, j + 1) ? 1 : 0;
    return count;
  }

  bool ok(vector<vector<int>> &board, int i, int j) { return i >= 0 && i < board.size() && j >= 0 && j < board[0].size() && (board[i][j] & 1) == 1; }

  void set(vector<vector<int>> &board, int i, int j) { board[i][j] |= 2; }

  int get(vector<vector<int>> &board, int i, int j) { return board[i][j] >> 1; }
};

void testGameOfLife()
{
  Solution s;
  vector<vector<int>> n1 = {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
  vector<vector<int>> n2 = {{1, 1}, {1, 0}};
  vector<vector<int>> o1 = {{0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 1, 0}};
  vector<vector<int>> o2 = {{1, 1}, {1, 1}};
  s.gameOfLife(n1);
  s.gameOfLife(n2);
  EXPECT_TRUE(o1 == n1);
  EXPECT_TRUE(o2 == n2);
  EXPECT_SUMMARY;
}

int main()
{
  testGameOfLife();
  return 0;
}
