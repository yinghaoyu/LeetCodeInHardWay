#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // dfs
  void solve1(vector<vector<char>> &board)
  {
    bool ans = false;
    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board[0].size(); j++)
      {
        if (board[i][j] == 'O')
        {
          ans = true;
          can(board, i, j, ans);
          board[i][j] = ans ? 'T' : 'F';
        }
      }
    }
    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board[0].size(); j++)
      {
        char can = board[i][j];
        if (can == 'T' || can == 'F')
        {
          board[i][j] = '.';
          change(board, i, j, can);
        }
      }
    }
  }

  void can(vector<vector<char>> &board, int i, int j, bool &ans)
  {
    if (i < 0 || i == board.size() || j < 0 || j == board[0].size())
    {
      ans = false;
      return;
    }
    if (board[i][j] == 'O')
    {
      board[i][j] = '.';
      can(board, i - 1, j, ans);
      can(board, i + 1, j, ans);
      can(board, i, j - 1, ans);
      can(board, i, j + 1, ans);
    }
  }

  void change(vector<vector<char>> &board, int i, int j, char can)
  {
    if (i < 0 || i == board.size() || j < 0 || j == board[0].size())
    {
      return;
    }
    if (board[i][j] == '.')
    {
      board[i][j] = can == 'T' ? 'X' : 'O';
      change(board, i - 1, j, can);
      change(board, i + 1, j, can);
      change(board, i, j - 1, can);
      change(board, i, j + 1, can);
    }
  }

  // 从边界开始感染的方法，比第一种方法更好
  void solve2(vector<vector<char>> &board)
  {
    if (board.size() == 0 || board[0].size() == 0)
    {
      return;
    }
    int N = board.size();
    int M = board[0].size();
    for (int j = 0; j < M; j++)
    {
      if (board[0][j] == 'O')
      {
        free(board, 0, j);
      }
      if (board[N - 1][j] == 'O')
      {
        free(board, N - 1, j);
      }
    }
    for (int i = 1; i < N - 1; i++)
    {
      if (board[i][0] == 'O')
      {
        free(board, i, 0);
      }
      if (board[i][M - 1] == 'O')
      {
        free(board, i, M - 1);
      }
    }
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        if (board[i][j] == 'O')
        {
          board[i][j] = 'X';
        }
        if (board[i][j] == 'F')
        {
          board[i][j] = 'O';
        }
      }
    }
  }

  void free(vector<vector<char>> &board, int i, int j)
  {
    if (i < 0 || i == board.size() || j < 0 || j == board[0].size() || board[i][j] != 'O')
    {
      return;
    }
    board[i][j] = 'F';
    free(board, i + 1, j);
    free(board, i - 1, j);
    free(board, i, j + 1);
    free(board, i, j - 1);
  }
};

void testSolve()
{
  Solution s;
  vector<vector<char>> b1 = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
  vector<vector<char>> o1 = {{'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'O', 'X', 'X'}};
  vector<vector<char>> b2 = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
  vector<vector<char>> o2 = {{'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'O', 'X', 'X'}};
  s.solve1(b1);
  s.solve2(b2);
  EXPECT_TRUE(b1 == o1);
  EXPECT_TRUE(b2 == o2);
  EXPECT_SUMMARY;
}

int main()
{
  testSolve();
  return 0;
}
