#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 二维树状数组
class NumMatrix
{
 public:
  NumMatrix(vector<vector<int>> &matrix)
  {
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
      return;
    }
    N = matrix.size();
    M = matrix[0].size();
    tree = vector<vector<int>>(N + 1, vector<int>(M + 1));
    nums = vector<vector<int>>(N, vector<int>(M));
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        update(i, j, matrix[i][j]);
      }
    }
  }

  int sum(int row, int col)
  {
    int sum = 0;
    for (int i = row + 1; i > 0; i -= lowBit(i))
    {
      for (int j = col + 1; j > 0; j -= lowBit(j))
      {
        sum += tree[i][j];
      }
    }
    return sum;
  }

  void update(int row, int col, int val)
  {
    if (N == 0 || M == 0)
    {
      return;
    }
    int add = val - nums[row][col];
    nums[row][col] = val;
    for (int i = row + 1; i <= N; i += lowBit(i))
    {
      for (int j = col + 1; j <= M; j += lowBit(j))
      {
        tree[i][j] += add;
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2)
  {
    if (N == 0 || M == 0)
    {
      return 0;
    }
    return sum(row2, col2) + sum(row1 - 1, col1 - 1) - sum(row1 - 1, col2) - sum(row2, col1 - 1);
  }

  int lowBit(int x)
  {
    return x & -x;
  }

 private:
  vector<vector<int>> tree;
  vector<vector<int>> nums;
  int N;
  int M;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
