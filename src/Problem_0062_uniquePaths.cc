#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 记忆化搜索
  int process(int c, int r, int x, int y, vector<vector<int>> &path)
  {
    if (c > x || r > y)
    {
      return 0;
    }
    if (c == x && r == y)
    {
      return 1;
    }
    if (path[c][r] != 0)
    {
      return path[c][r];
    }
    int p1 = process(c + 1, r, x, y, path);
    int p2 = process(c, r + 1, x, y, path);
    path[c][r] = p1 + p2;
    return p1 + p2;
  }

  int uniquePaths(int m, int n)
  {
    vector<vector<int>> path(m, vector<int>(n));
    return process(0, 0, m - 1, n - 1, path);
  }

  // 递归改动态规划
  int dp(int m, int n)
  {
    vector<vector<int>> dp(m, vector<int>(n));
    dp[m - 1][n - 1] = 1;
    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = n - 1; j >= 0; j--)
      {
        if (i == m - 1 || j == n - 1)
        {
          dp[i][j] = 1;
        }
        else
        {
          dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
        }
      }
    }
    return dp[0][0];
  }

  // 数学
  // 从左上角到右下角的过程中，我们需要移动 m+n−2 次，其中有
  // m−1 次向下移动，n−1 次向右移动。
  // 因此路径的总数，就等于从 m+n−2 次移动中选择 m−1 次向下移动的方案数
  int math(int m, int n)
  {
    int part = n - 1;
    int all = m + n - 2;
    long o1 = 1;
    long o2 = 1;
    for (int i = part + 1, j = 1; i <= all || j <= all - part; i++, j++)
    {
      o1 *= i;
      o2 *= j;
      long g = gcd(o1, o2);
      o1 /= g;
      o2 /= g;
    }
    return (int) o1;
  }

  // 调用的时候，请保证初次调用时，m和n都不为0
  long gcd(long m, long n) { return n == 0 ? m : gcd(n, m % n); }
};

void testUniquePaths()
{
  Solution s;
  EXPECT_EQ_INT(3, s.uniquePaths(3, 2));
  EXPECT_EQ_INT(28, s.uniquePaths(3, 7));
  EXPECT_EQ_INT(3, s.dp(3, 2));
  EXPECT_EQ_INT(28, s.dp(3, 7));
  EXPECT_EQ_INT(3, s.math(3, 2));
  EXPECT_EQ_INT(28, s.math(3, 7));
  EXPECT_SUMMARY;
}

int main()
{
  testUniquePaths();
  return 0;
}
