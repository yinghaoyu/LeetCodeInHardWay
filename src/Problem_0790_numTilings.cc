#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 蒙德里安的梦想
// https://github.com/yinghaoyu/algorithms/blob/master/dp/PavingTile.cc

class Solution
{
 public:
  // 暴力解
  // 为了找规律
  // 如果h==0，返回2*n的区域铺满的方法数
  // 如果h==1，返回1 + 2*n的区域铺满的方法数
  long f(int n, int h)
  {
    if (n == 0)
    {
      return h == 0 ? 1 : 0;
    }
    if (n == 1)
    {
      return 1;
    }
    if (h == 1)
    {
      return f(n - 1, 0) + f(n - 1, 1);
    }
    else
    {
      return f(n - 1, 0) + f(n - 2, 0) + 2 * f(n - 2, 1);
    }
  }

  int numTilings1(int n) { return f(n, 0); }

  // dp
  // 考虑这么一种平铺的方式：在第 i 列前面的正方形都被瓷砖覆盖，在第 i
  // 列后面的正方形都没有被瓷砖覆盖（i 从 1 开始计数）。 那么第 i 列的正方形有四种被覆盖的情况： 0.
  // 一个正方形都没有被覆盖，记为状态 0；
  // 1. 只有上方的正方形被覆盖，记为状态 1；
  // 2. 只有下方的正方形被覆盖，记为状态 2；
  // 3. 上下两个正方形都被覆盖，记为状态 3。
  int numTilings2(int n)
  {
    int mod = 1e9 + 7;
    vector<vector<long long>> dp(n + 1, vector<long long>(4));
    // base case
    dp[0][3] = 1;
    for (int i = 1; i <= n; i++)
    {
      // 为什么这里不包含dp[i-1][0] ？
      // 因为此时放置的瓷砖，仅对第 i −1 列产生影响，不会对第 i
      // 列产生影响，该决策所产生的方案数，已在 dp[i−1][X] 时被统计
      dp[i][0] = dp[i - 1][3] /*+ dp[i-1][0]*/;
      dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
      dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
      dp[i][3] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3]) % mod;
    }
    return dp[n][3];
  }

  // 最优解，快速幂
  int numTilings(int n) { return f2(n - 1); }

  static constexpr int MOD = 1000000007;

  int f2(int n)
  {
    if (n == 0)
    {
      return 1;
    }
    if (n == 1)
    {
      return 2;
    }
    if (n == 2)
    {
      return 5;
    }
    vector<vector<int>> start = {{5, 2, 1}};
    vector<vector<int>> base = {{2, 1, 0}, {0, 0, 1}, {1, 0, 0}};
    vector<vector<int>> ans = multiply(start, power(base, n - 2));
    return ans[0][0];
  }

  // 矩阵相乘 + 乘法取模
  // a的列数一定要等于b的行数
  vector<vector<int>> multiply(vector<vector<int>>& a, vector<vector<int>> b)
  {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        for (int c = 0; c < k; c++)
        {
          ans[i][j] = (int) (((long) a[i][c] * b[c][j] + ans[i][j]) % MOD);
        }
      }
    }
    return ans;
  }

  // 矩阵快速幂
  vector<vector<int>> power(vector<vector<int>>& m, int p)
  {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
      ans[i][i] = 1;
    }
    for (; p != 0; p >>= 1)
    {
      if ((p & 1) != 0)
      {
        ans = multiply(ans, m);
      }
      m = multiply(m, m);
    }
    return ans;
  }
};

void testNumTilings()
{
  Solution s;
  EXPECT_EQ_INT(5, s.numTilings2(3));
  EXPECT_EQ_INT(1, s.numTilings2(1));
  EXPECT_SUMMARY;
}

int main()
{
  testNumTilings();
  return 0;
}
