#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  string tictactoe(vector<string>& board)
  {
    int N = board.size();
    bool is_full = true;
    bool XDiaWin = true, ODiaWin = true;
    bool XiDiaWin = true, OiDiaWin = true;

    for (int i = 0; i < N; ++i)
    {
      bool XRowWin = true, XColWin = true;
      bool ORowWin = true, OColWin = true;

      for (int j = 0; j < N; ++j)
      {
        if (board[i][j] == ' ')
        {
          // 有未填满的情况
          is_full = false;
        }
        XRowWin = XRowWin && (board[i][j] == 'X');
        XColWin = XColWin && (board[j][i] == 'X');
        ORowWin = ORowWin && (board[i][j] == 'O');
        OColWin = OColWin && (board[j][i] == 'O');
      }

      if (XRowWin || XColWin)
      {
        return "X";
      }
      else if (ORowWin || OColWin)
      {
        return "O";
      }

      // 对角线验证
      XDiaWin = XDiaWin && (board[i][i] == 'X');
      ODiaWin = ODiaWin && (board[i][i] == 'O');
      XiDiaWin = XiDiaWin && (board[i][N - 1 - i] == 'X');
      OiDiaWin = OiDiaWin && (board[i][N - 1 - i] == 'O');
    }

    if (XDiaWin || XiDiaWin)
    {
      return "X";
    }
    else if (ODiaWin || OiDiaWin)
    {
      return "O";
    }

    if (is_full)
    {
      return "Draw";
    }

    return "Pending";
  }
};
