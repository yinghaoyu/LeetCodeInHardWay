#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

using TdArray = vector<vector<int>>;

class Solution
{
 public:
  // 思路：
  // 如果不考虑限制
  // vector<bool> row(m)
  // vector<bool> col(n)
  // 可以用两个数组标记哪行、哪列需要清0
  //
  // 考虑限制，就可以在原二维数组上取第0行、第0列代替row、col数组
  // 需要注意的是，第0行、第0列本身存在的0需要提前考虑
  void setZeroes1(vector<vector<int>> &matrix)
  {
    bool row = false;
    bool col = false;
    for (int i = 0; i < matrix.size(); i++)
    {
      if (matrix[i][0] == 0)
      {
        col = true;
        break;
      }
    }
    for (int i = 0; i < matrix[0].size(); i++)
    {
      if (matrix[0][i] == 0)
      {
        row = true;
        break;
      }
    }
    for (int i = 1; i < matrix.size(); i++)
    {
      for (int j = 1; j < matrix[0].size(); j++)
      {
        if (matrix[i][j] == 0)
        {
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }
    for (int i = 1; i < matrix.size(); i++)
    {
      for (int j = 1; j < matrix[0].size(); j++)
      {
        if (matrix[0][j] == 0 || matrix[i][0] == 0)
        {
          matrix[i][j] = 0;
        }
      }
    }
    if (col)
    {
      for (int i = 0; i < matrix.size(); i++)
      {
        matrix[i][0] = 0;
      }
    }
    if (row)
    {
      for (int i = 0; i < matrix[0].size(); i++)
      {
        matrix[0][i] = 0;
      }
    }
  }

  // 优化
  void setZeroes2(vector<vector<int>> &matrix)
  {
    // 第0列的数，表示行要不要清0
    // 其他列的数，表示列要不要清0
    bool col = false;
    for (int i = 0; i < matrix.size(); i++)
    {
      for (int j = 0; j < matrix[0].size(); j++)
      {
        if (matrix[i][j] == 0)
        {
          matrix[i][0] = 0;
          if (j == 0)
          {
            // 说明第0列存在0，后续需要把第0列清0
            col = true;
          }
          else
          {
            // matrix[0][0] 表示第0行要不要清0，第0列要不要清0由col表示
            // 不能破坏第0行的规则
            matrix[0][j] = 0;
          }
        }
      }
    }
    // 最后才清空第一行
    for (int i = matrix.size() - 1; i >= 0; i++)
    {
      for (int j = 1; j < matrix[0].size(); j++)
      {
        if (matrix[i][0] == 0 || matrix[0][j] == 0)
        {
          matrix[i][j] = 0;
        }
      }
    }
    if (col)
    {
      for (int i = 0; i < matrix.size(); i++)
      {
        matrix[i][0] = 0;
      }
    }
  }
};

bool isTdArrayEqual(TdArray a, TdArray b)
{
  for (int i = 0; i < a.size(); i++)
  {
    for (int j = 0; j < b.size(); j++)
    {
      if (a[i][j] != b[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

void testSetZeroes()
{
  Solution s;

  TdArray in1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  TdArray out1 = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};

  TdArray in2 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  TdArray out2 = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};

  TdArray in3 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  TdArray out3 = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};

  s.setZeroes1(in1);
  s.setZeroes1(in2);
  s.setZeroes1(in3);

  EXPECT_TRUE(isTdArrayEqual(out1, in1));
  EXPECT_TRUE(isTdArrayEqual(out2, in2));
  EXPECT_TRUE(isTdArrayEqual(out3, in3));

  TdArray in4 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  TdArray in5 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  TdArray in6 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

  s.setZeroes2(in4);
  s.setZeroes2(in5);
  s.setZeroes2(in6);

  EXPECT_TRUE(isTdArrayEqual(out1, in4));
  EXPECT_TRUE(isTdArrayEqual(out2, in5));
  EXPECT_TRUE(isTdArrayEqual(out3, in6));
  EXPECT_SUMMARY;
}

int main()
{
  testSetZeroes();
  return 0;
}
