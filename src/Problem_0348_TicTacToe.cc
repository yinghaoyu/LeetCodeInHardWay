#include <iostream>
#include <vector>

using namespace std;

class TicTacToe
{
 private:
  vector<vector<int>> rows;
  vector<vector<int>> cols;
  vector<int> leftUp;
  vector<int> rightUp;
  vector<vector<bool>> matrix;
  int N;

 public:
  TicTacToe(int n)
  {
    rows = vector<vector<int>>(n, vector<int>(3));
    cols = vector<vector<int>>(n, vector<int>(3));
    leftUp = vector<int>(3);
    rightUp = vector<int>(3);
    matrix = vector<vector<bool>>(n, vector<bool>(n));
    N = n;
  }

  int move(int row, int col, int player)
  {
    if (matrix[row][col])
    {
      return 0;
    }
    matrix[row][col] = true;
    rows[row][player]++;
    cols[col][player]++;
    if (row == col)
    {
      leftUp[player]++;
    }
    if (row + col == N - 1)
    {
      rightUp[player]++;
    }
    if (rows[row][player] == N || cols[col][player] == N || leftUp[player] == N || rightUp[player] == N)
    {
      return player;
    }
    return 0;
  }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */
