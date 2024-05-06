#include <vector>

using namespace std;

class Solution
{
 public:
  void f(vector<vector<char>>& board, int x, int y)
  {
    if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size())
    {
      // 越界或者已经是揭开空白块
      return;
    }
    if (board[x][y] == 'M')
    {
      // 碰到地雷
      board[x][y] = 'X';
      return;
    }
    if (board[x][y] != 'E')
    {
      // 已经揭开不需要扩展
      return;
    }

    int mine = 0;
    for (int dx = -1; dx <= 1; dx++)
    {
      for (int dy = -1; dy <= 1; dy++)
      {
        int nextx = x + dx;
        int nexty = y + dy;
        if (nextx < 0 || nextx >= board.size() || nexty < 0 || nexty >= board[0].size() ||
            (nextx == x && nexty == y))
        {
          continue;
        }
        mine += board[nextx][nexty] == 'M';
      }
    }
    if (mine == 0)
    {
      board[x][y] = 'B';
      f(board, x - 1, y - 1);
      f(board, x - 1, y);
      f(board, x - 1, y + 1);
      f(board, x, y - 1);
      f(board, x, y + 1);
      f(board, x + 1, y - 1);
      f(board, x + 1, y);
      f(board, x + 1, y + 1);
    }
    else
    {
      board[x][y] = mine + '0';
    }
  }

  vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click)
  {
    int x = click[0];
    int y = click[1];
    f(board, x, y);
    return board;
  }
};
