#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 递归，时间复杂度O(n)
  int climbStairs1(int n)
  {
    if (n == 1)
    {
      return 1;
    }
    else if (n == 2)
    {
      return 2;
    }
    else
    {
      return climbStairs1(n - 1) + climbStairs1(n - 2);
    }
  }

  // 动态规划，时间复杂度O(n)
  int climbStairs2(int n)
  {
    if (n == 1)
    {
      return 1;
    }
    if (n == 2)
    {
      return 2;
    }
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++)
    {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }

  // 动态规划空间优化
  int climbStairs3(int n)
  {
    if (n == 1)
    {
      return 1;
    }
    if (n == 2)
    {
      return 2;
    }
    int a = 1;
    int b = 2;
    int c = 0;
    for (int i = 3; i <= n; i++)
    {
      c = a + b;
      a = b;
      b = c;
    }
    return c;
  }

  // 齐次方程解，时间复杂度O(lgN)
  int climbStairs4(int n)
  {
    // TODO: figure it out
    if (n < 1)
    {
      return 0;
    }
    if (n == 1 || n == 2)
    {
      return n;
    }
    vector<vector<int>> base = {{1, 1}, {1, 0}};
    vector<vector<int>> res = matrixPower(base, n - 2);
    return 2 * res[0][0] + res[1][0];
  }

  vector<vector<int>> matrixPower(vector<vector<int>> &m, int p)
  {
    vector<vector<int>> res(m.size(), vector<int>(m[0].size()));
    for (int i = 0; i < res.size(); i++)
    {
      res[i][i] = 1;
    }

    // res = 矩阵中的1
    vector<vector<int>> tmp = m;  // 矩阵1次方
    for (; p != 0; p >>= 1)
    {
      if ((p & 1) != 0)
      {
        res = muliMatrix(res, tmp);
      }
      tmp = muliMatrix(tmp, tmp);
    }
    return res;
  }

  // 两个矩阵乘完之后的结果返回
  vector<vector<int>> muliMatrix(vector<vector<int>> &m1, vector<vector<int>> &m2)
  {
    vector<vector<int>> res(m1.size(), vector<int>(m2[0].size()));
    for (int i = 0; i < m1.size(); i++)
    {
      for (int j = 0; j < m2[0].size(); j++)
      {
        for (int k = 0; k < m2.size(); k++)
        {
          res[i][j] += m1[i][k] * m2[k][j];
        }
      }
    }
    return res;
  }
};

void testClimbStairs()
{
  Solution s;
  EXPECT_EQ_INT(2, s.climbStairs1(2));
  EXPECT_EQ_INT(3, s.climbStairs1(3));
  EXPECT_EQ_INT(1346269, s.climbStairs1(30));
  EXPECT_EQ_INT(2, s.climbStairs2(2));
  EXPECT_EQ_INT(3, s.climbStairs2(3));
  EXPECT_EQ_INT(1346269, s.climbStairs2(30));
  EXPECT_EQ_INT(2, s.climbStairs3(2));
  EXPECT_EQ_INT(3, s.climbStairs3(3));
  EXPECT_EQ_INT(1346269, s.climbStairs3(30));
  EXPECT_EQ_INT(2, s.climbStairs4(2));
  EXPECT_EQ_INT(3, s.climbStairs4(3));
  EXPECT_EQ_INT(1346269, s.climbStairs4(30));
  EXPECT_SUMMARY;
}

int main()
{
  testClimbStairs();
  return 0;
}
