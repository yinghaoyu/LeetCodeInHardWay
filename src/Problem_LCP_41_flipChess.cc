#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 以一个方向走到底，是否以黑棋为结尾
  bool judge(const vector<string> &chessboard, int x, int y, int dx, int dy)
  {
    x += dx;
    y += dy;
    while (0 <= x && x < chessboard.size() && 0 <= y && y < chessboard[0].size())
    {
      if (chessboard[x][y] == 'X')
      {
        return true;
      }
      else if (chessboard[x][y] == '.')
      {
        return false;
      }
      x += dx;
      y += dy;
    }
    return false;
  }

  int bfs(vector<string> chessboard, int px, int py)
  {
    const int dirs[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int cnt = 0;
    queue<std::pair<int, int>> q;
    q.emplace(px, py);
    chessboard[px][py] = 'X';
    while (!q.empty())
    {
      auto t = q.front();
      q.pop();
      for (int i = 0; i < 8; i++)
      {
        if (judge(chessboard, t.first, t.second, dirs[i][0], dirs[i][1]))
        {
          int x = t.first + dirs[i][0];
          int y = t.second + dirs[i][1];
          while (chessboard[x][y] != 'X')
          {
            // 将所有白棋子变成黑棋子
            q.emplace(x, y);
            chessboard[x][y] = 'X';
            x += dirs[i][0];
            y += dirs[i][1];
            ++cnt;
          }
        }
      }
    }
    return cnt;
  }

  int flipChess(vector<string> &chessboard)
  {
    int ans = 0;
    for (int i = 0; i < chessboard.size(); i++)
    {
      for (int j = 0; j < chessboard[0].size(); j++)
      {
        if (chessboard[i][j] == '.')
        {
          ans = std::max(ans, bfs(chessboard, i, j));
        }
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> c1 = {"....X.", "....X.", "XOOO..", "......", "......"};
  vector<string> c2 = {".X.", ".O.", "XO."};
  vector<string> c3 = {".......", ".......", ".......", "X......", ".O.....", "..O....", "....OOX"};
  EXPECT_EQ_INT(3, s.flipChess(c1));
  EXPECT_EQ_INT(2, s.flipChess(c2));
  EXPECT_EQ_INT(4, s.flipChess(c3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
