#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void setZeroes1(vector<vector<int>> &matrix)
  {
    // 第0行保存所有列的状态
    // 第0列保存所有行的状态
    bool row = false;
    bool col = false;
    for (int i = 0; i < matrix.size(); i++)
    {
      if (matrix[i][0] == 0)
      {
        col = true;
      }
    }
    for (int j = 0; j < matrix[0].size(); j++)
    {
      if (matrix[0][j] == 0)
      {
        row = true;
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
    if (row)
    {
      for (int j = 0; j < matrix[0].size(); j++)
      {
        matrix[0][j] = 0;
      }
    }
  }

  void setZeroes2(vector<vector<int>> &matrix)
  {
    // 第0列保存所有行的状态
    bool col0 = false;
    for (int i = 0; i < matrix.size(); i++)
    {
      for (int j = 0; j < matrix[0].size(); j++)
      {
        if (matrix[i][j] == 0)
        {
          matrix[i][0] = 0;
          if (j == 0)
          {
            // 因为第0列的数表示的是行要不要清0，第0列要不要清0用col0记录
            // 例如matrix[1][0]的含义是第1行要不要清0，因此不能改这个值
            col0 = true;
          }
          else
          {
            matrix[0][j] = 0;
          }
        }
      }
    }
    for (int i = matrix.size() - 1; i >= 0; i--)
    {
      for (int j = 1; j < matrix[0].size(); j++)
      {
        if (matrix[i][0] == 0 || matrix[0][j] == 0)
        {
          matrix[i][j] = 0;
        }
      }
    }
    if (col0)
    {
      for (int i = 0; i < matrix.size(); i++)
      {
        matrix[i][0] = 0;
      }
    }
  }
};

bool isVectorEuqal(vector<vector<int>> a, vector<vector<int>> b)
{
  return a == b;
}

void testSetZeroes()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  vector<vector<int>> o1 = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};
  vector<vector<int>> n2 = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
  vector<vector<int>> o2 = {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}};
  s.setZeroes1(n1);
  s.setZeroes1(n2);
  vector<vector<int>> x1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  vector<vector<int>> y1 = {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}};
  vector<vector<int>> x2 = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
  vector<vector<int>> y2 = {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}};
  s.setZeroes2(x1);
  s.setZeroes2(x2);
  EXPECT_TRUE(isVectorEuqal(o1, n1));
  EXPECT_TRUE(isVectorEuqal(o2, n2));
  EXPECT_TRUE(isVectorEuqal(y1, x1));
  EXPECT_TRUE(isVectorEuqal(y2, x2));
  EXPECT_SUMMARY;
}

int main()
{
  testSetZeroes();
  return 0;
}
