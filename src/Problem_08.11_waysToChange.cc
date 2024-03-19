#include <vector>

using namespace std;

class Solution
{
 private:
  static constexpr int MOD = 1e9 + 7;
  vector<int> coins = {1, 5, 10, 25};

 public:
  int f1(int rest, int index)
  {
    if (index == coins.size())
    {
      return rest == 0;
    }
    if (rest < 0)
    {
      return 0;
    }
    int ways = 0;
    for (int zhang = 0; zhang * coins[index] <= rest; zhang++)
    {
      ways += f1(rest - zhang * coins[index], index + 1);
    }
    return ways;
  }

  // 暴力递归，超时
  int waysToChange1(int n) { return f1(n, 0); }

  // 动态规划，超时
  int waysToChange2(int n)
  {
    int m = coins.size();
    // dp[i][j]的含义为：前 i 种硬币能组合总面值 j 的方法数
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    // base case
    dp[m][0] = 1;
    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = 0; j <= n; j++)
      {
        for (int k = 0; k * coins[i] <= j; k++)
        {
          dp[i][j] = (dp[i][j] + dp[i + 1][j - k * coins[i]]) % MOD;
        }
      }
    }
    return dp[0][n];
  }

  // 动态规划，斜率优化，56ms
  int waysToChange3(int n)
  {
    int m = coins.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    dp[m][0] = 1;
    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = 0; j <= n; j++)
      {
        dp[i][j] = dp[i + 1][j];
        if (j - coins[i] > 0)
        {
          // 斜率优化，直接观察得出
          dp[i][j] = (dp[i][j] + dp[i][j - coins[i]]) % MOD;
        }
      }
    }
    return dp[0][n];
  }

  // 动态规划，斜率优化 + 空间优化，27ms
  int waysToChange4(int n)
  {
    int m = coins.size();
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = coins[i]; j <= n; j++)
      {
        dp[j] = (dp[j] + dp[j - coins[i]]) % MOD;
      }
    }
    return dp[n];
  }
};
