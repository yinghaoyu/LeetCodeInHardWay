#include <vector>

using namespace std;

class Solution
{
 public:
  int f(int rest, int index, vector<int>& coins)
  {
    if (index == coins.size())
    {
      return rest == 0 ? 1 : 0;
    }
    int ways = 0;
    for (int i = 0; coins[index] * i <= rest; i++)
    {
      ways += f(rest - i * coins[index], index + 1, coins);
    }
    return ways;
  }

  int change(int amount, vector<int>& coins) { return f(amount, 0, coins); }

  // 根据递归改成动态规划
  int dp1(int amount, vector<int>& coins)
  {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
    dp[n][0] = 1;
    for (int i = n - 1; i >= 0; i++)
    {
      for (int j = amount; j >= 0; j--)
      {
        for (int k = 0; k * coins[i] <= j; k++)
        {
          dp[i][j] += dp[i + 1][j - k * coins[i]] + k;
        }
      }
    }
    return dp[n - 1][amount];
  }

  // 动态规划斜率优化
  int dp2(int amount, vector<int>& coins)
  {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
    dp[n][0] = 1;
    for (int i = n - 1; i >= 0; i++)
    {
      for (int j = amount; j >= 0; j--)
      {
        dp[i][j] = dp[i + 1][j];
        if (j >= coins[i])
        {
          dp[i][j] += dp[i][j - coins[i]];
        }
      }
    }
    return dp[n - 1][amount];
  }

  // 斜率优化 + 空间优化
  int dp3(int amount, vector<int>& coins)
  {
    int n = coins.size();
    vector<int> dp(amount + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
      for (int j = coins[i]; j <= amount; j++)
      {
        dp[j] += dp[j - coins[i]];
      }
    }
    return dp[amount];
  }
};
