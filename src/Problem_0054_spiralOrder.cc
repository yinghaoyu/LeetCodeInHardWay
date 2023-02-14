#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> spiralOrder(vector<vector<int>> &matrix)
  {
    vector<int> ans;
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
      return ans;
    }
    int a = 0;
    int b = 0;
    int c = matrix.size() - 1;
    int d = matrix[0].size() - 1;
    while (a <= c && b <= d)
    {
      addEdge(matrix, a++, b++, c--, d--, ans);
    }
    return ans;
  }

  void addEdge(vector<vector<int>> &matrix, int a, int b, int c, int d, vector<int> &ans)
  {
    if (a == c)
    {
      // 只剩单行
      for (int i = b; i <= d; i++)
      {
        ans.push_back(matrix[a][i]);
      }
    }
    else if (b == d)
    {
      // 只剩单列
      for (int i = a; i <= c; i++)
      {
        ans.push_back(matrix[i][b]);
      }
    }
    else
    {
      // 开始画圈
      int curR = a;
      int curC = b;
      while (curC != d)
      {
        ans.push_back(matrix[a][curC]);
        curC++;
      }
      while (curR != c)
      {
        ans.push_back(matrix[curR][d]);
        curR++;
      }
      while (curC != b)
      {
        ans.push_back(matrix[c][curC]);
        curC--;
      }
      while (curR != a)
      {
        ans.push_back(matrix[curR][b]);
        curR--;
      }
    }
  }
}
;

void testSpiralOrder()
{
  Solution s;
  vector<vector<int>> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<int> o1 = {1, 2, 3, 6, 9, 8, 7, 4, 5};
  vector<vector<int>> m2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
  vector<int> o2 = {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
  EXPECT_TRUE(o1 == s.spiralOrder(m1));
  EXPECT_TRUE(o2 == s.spiralOrder(m2));
  EXPECT_SUMMARY;
}

int main()
{
  testSpiralOrder();
  return 0;
}
