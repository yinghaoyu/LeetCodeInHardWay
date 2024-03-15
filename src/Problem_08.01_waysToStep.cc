#include <vector>

using namespace std;

class Solution
{
 private:
  const static int MOD = 1e9 + 7;

 public:
  // 动态规划
  int waysToStep1(int n)
  {
    vector<long> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
      if (i - 1 >= 0)
      {
        dp[i] = (dp[i] + dp[i - 1]) % MOD;
      }
      if (i - 2 >= 0)
      {
        dp[i] = (dp[i] + dp[i - 2]) % MOD;
      }
      if (i - 3 >= 0)
      {
        dp[i] = (dp[i] + dp[i - 3]) % MOD;
      }
    }
    return dp[n];
  }

  // 矩阵快速幂
  // | 1 1 1 |   | f(n-1) |   |  f(n)  |
  // | 1 0 0 | * | f(n-2) | = | f(n-1) |
  // | 0 1 0 |   | f(n-3) |   | f(n-2) |
  int waysToStep2(int n)
  {
    if (n == 1)
    {
      return 1;
    }
    if (n == 2)
    {
      return 2;
    }
    if (n == 3)
    {
      return 4;
    }
    vector<vector<long>> base = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}};
    vector<vector<long>> ans = matrixPower(base, n - 3);
    return (4 * ans[0][0] + 2 * ans[0][1] + ans[0][2]) % MOD;
  }

  vector<vector<long>> matrixPower(const vector<vector<long>>& m, int p)
  {
    vector<vector<long>> res(m.size(), vector<long>(m[0].size()));
    for (int i = 0; i < m.size(); i++)
    {
      res[i][i] = 1;
    }
    // res = 矩阵中的1
    vector<vector<long>> t(m);  // 矩阵1次方
    for (; p != 0; p >>= 1)
    {
      if ((p & 1) != 0)  // p为奇数
      {
        res = muliMatrix(res, t);
      }
      t = muliMatrix(t, t);  // 快速幂
    }
    return res;
  }

  // 两个矩阵乘完之后的结果返回
  vector<vector<long>> muliMatrix(const vector<vector<long>>& m1, const vector<vector<long>>& m2)
  {
    vector<vector<long>> res(m1.size(), vector<long>(m1[0].size()));
    for (int i = 0; i < m1.size(); i++)
    {
      for (int j = 0; j < m2[0].size(); j++)
      {
        for (int k = 0; k < m2.size(); k++)
        {
          res[i][j] = (res[i][j] + m1[i][k] * m2[k][j]) % MOD;
        }
      }
    }
    return res;
  }
};
