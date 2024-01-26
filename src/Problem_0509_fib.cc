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

  // TODO: 矩阵快速幂
  int fib5(int n) { return 0; }
};
