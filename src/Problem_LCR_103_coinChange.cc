#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/coin-change/
// @sa Problem_0322_coinChange.cc
class Solution
{
 public:
  // 没有优化过的完全背包，需要三重循环
  int coinChange(vector<int>& coins, int amount)
  {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
    for (int j = 1; j <= amount; j++)
    {
      // 所有硬币都遍历完了，还是有剩余，说明拼不出
      dp[n][j] = -1;
    }
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = 0; j <= amount; j++)
      {
        dp[i][j] = -1;
        if (dp[i + 1][j] != -1)
        {
          // 不取当前硬币
          dp[i][j] = dp[i + 1][j];
        }
        // 取当前硬币
        for (int k = 0; k * coins[i] <= j; k++)
        {
          if (dp[i][j - k * coins[i]] != -1)
          {
            if (dp[i][j] == -1)
            {
              dp[i][j] = dp[i][j - k * coins[i]] + k;
            }
            else
            {
              dp[i][j] = std::min(dp[i][j], dp[i][j - k * coins[i]] + k);
            }
          }
        }
      }
    }
    return dp[0][amount];
  }

  // 优化过的完全背包问题，只需要两重循环
  int dp(vector<int>& coins, int amount)
  {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
    for (int j = 1; j <= amount; j++)
    {
      dp[n][j] = -1;
    }
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = 0; j <= amount; j++)
      {
        dp[i][j] = -1;
        if (dp[i + 1][j] != -1)
        {
          // 不取当前硬币
          dp[i][j] = dp[i + 1][j];
        }
        // 取当前硬币
        if (j - coins[i] >= 0 && dp[i][j - coins[i]] != -1)
        {
          if (dp[i][j] == -1)
          {
            dp[i][j] = dp[i][j - coins[i]] + 1;
          }
          else
          {
            dp[i][j] = std::min(dp[i][j], dp[i][j - coins[i]] + 1);
          }
        }
      }
    }
    return dp[0][amount];
  }
};
