#include <vector>

using namespace std;

class Solution
{
 public:
  // 递归
  int fib1(int n) { return f1(n); }

  int f1(int i)
  {
    if (i == 0)
    {
      return 0;
    }
    else if (i == 1)
    {
      return 1;
    }
    else
    {
      return f1(i - 1) + f1(i - 2);
    }
  }

  // 记忆化搜索
  int fib2(int n)
  {
    vector<int> dp(n + 1, -1);
    return f2(n, dp);
  }

  int f2(int i, vector<int>& dp)
  {
    if (i == 0)
    {
      return 0;
    }
    if (i == 1)
    {
      return 1;
    }
    if (dp[i] != -1)
    {
      return dp[i];
    }
    int ans = f2(i - 1, dp) + f2(i - 2, dp);
    dp[i] = ans;
    return ans;
  }

  // 动态规划
  int fib3(int n)
  {
    if (n == 0)
    {
      return 0;
    }
    if (n == 1)
    {
      return 1;
    }
    vector<int> dp(n + 1);
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }

  // 动态规划，空间优化
  int fib4(int n)
  {
    if (n == 0)
    {
      return 0;
    }
    if (n == 1)
    {
      return 1;
    }
    int lastLast = 0, last = 1;
    for (int i = 2, cur; i <= n; i++)
    {
      cur = lastLast + last;
      lastLast = last;
      last = cur;
    }
    return last;
  }

  // 最优解，矩阵快速幂，O(log(n))
  int fib5(int n)
  {
    if (n == 0)
    {
      return 0;
    }
    if (n == 1)
    {
      return 1;
    }
    vector<vector<int>> start = {{1, 0}};
    vector<vector<int>> base = {{1, 1}, {1, 0}};
    vector<vector<int>> ans = multiply(start, power(base, n - 1));
    return ans[0][0];
  }

  // 矩阵相乘
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
          ans[i][j] += a[i][c] * b[c][j];
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
      if (p & 1)
      {
        ans = multiply(ans, m);
      }
      m = multiply(m, m);
    }
    return ans;
  }
};
