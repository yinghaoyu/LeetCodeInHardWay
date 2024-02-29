#include <cstdint>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int f(vector<int>& coins, int index, int amount)
  {
    if (index == coins.size())
    {
      return amount == 0 ? 0 : INT32_MAX;
    }
    int ways = INT32_MAX;
    for (int zhang = 0; zhang * coins[index] <= amount; zhang++)
    {
      int next = f(coins, index + 1, amount - zhang * coins[index]);
      if (next != INT32_MAX)
      {
        ways = std::min(ways, next + zhang);
      }
    }
    return ways;
  }

  // 暴力尝试，超时
  int coinChange1(vector<int>& coins, int amount)
  {
    if (amount == 0)
    {
      return 0;
    }
    int ans = f(coins, 0, amount);
    return ans == INT32_MAX ? -1 : ans;
  }

  int dfs(vector<int>& coins, int index, vector<int>& seen, int amount)
  {
    if (index == coins.size())
    {
      return amount == 0 ? 0 : INT32_MAX;
    }
    if (seen[amount] != INT32_MAX)
    {
      return seen[amount];
    }
    int ways = INT32_MAX;
    for (int zhang = 0; zhang * coins[index] <= amount; zhang++)
    {
      int next = dfs(coins, index + 1, seen, amount - zhang * coins[index]);
      if (next != INT32_MAX)
      {
        ways = std::min(ways, next + zhang);
      }
    }
    // 注意这里的 ways 也有可能是 INT32_MAX
    // 假如seen数组的初始值为 -1，
    // if(seen[amount] != -1) return seen[amount]; 会把 INT32_MAX 返回，导致没有计算某个步骤
    seen[amount] = ways;
    return ways;
  }

  // 记忆化搜索，超时
  int coinChange2(vector<int>& coins, int amount)
  {
    if (amount == 0)
    {
      return 0;
    }
    vector<int> seen(amount + 1, INT32_MAX);
    int ans = dfs(coins, 0, seen, amount);
    return ans == INT32_MAX ? -1 : ans;
  }

  // 递归改dp
  int coinChange3(vector<int>& coins, int amount)
  {
    if (coins.size() == 0 || amount < 0)
    {
      return -1;
    }
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1));
    for (int j = 1; j <= amount; j++)
    {
      // 数组到尽头，还有剩余
      dp[n][j] = -1;
    }
    for (int i = n - 1; i >= 0; i--)
    {
      for (int rest = 0; rest <= amount; rest++)
      {
        dp[i][rest] = -1;
        if (dp[i + 1][rest] != -1)
        {
          // 不用当前面值
          dp[i][rest] = dp[i + 1][rest];
        }
        if (rest - coins[i] >= 0 && dp[i][rest - coins[i]] != -1)
        {
          // 用当前面值
          if (dp[i][rest] == -1)
          {
            dp[i][rest] = dp[i][rest - coins[i]] + 1;
          }
          else
          {
            dp[i][rest] = std::min(dp[i][rest], dp[i][rest - coins[i]] + 1);
          }
        }
      }
    }
    return dp[0][amount];
  }

  int coinChange4(vector<int>& coins, int aim)
  {
    if (coins.size() == 0 || aim < 0)
    {
      return -1;
    }
    int N = coins.size();
    vector<vector<int>> dp(N, vector<int>(aim + 1));
    // dp[i][0] = 0 0列不需要填
    // dp[0][1...] = arr[0]的整数倍，有张数，倍数，其他的格子-1（表示无方案）
    for (int j = 1; j <= aim; j++)
    {
      if (j % coins[0] != 0)
      {
        dp[0][j] = -1;
      }
      else
      {
        dp[0][j] = j / coins[0];
      }
    }

    for (int i = 1; i < N; i++)
    {
      for (int j = 1; j <= aim; j++)
      {
        dp[i][j] = INT32_MAX;
        if (dp[i - 1][j] != -1)
        {
          dp[i][j] = dp[i - 1][j];
        }
        if (j - coins[i] >= 0 && dp[i][j - coins[i]] != -1)
        {
          dp[i][j] = std::min(dp[i][j], dp[i][j - coins[i]] + 1);
        }
        if (dp[i][j] == INT32_MAX)
        {
          dp[i][j] = -1;
        }
      }
    }
    return dp[N - 1][aim];
  }
};

void testCoinChange()
{
  Solution s;
  vector<int> n1 = {1, 2, 5};
  vector<int> n2 = {2};
  vector<int> n3 = {1};
  vector<int> n4 = {1, 2, 5, 10};
  EXPECT_EQ_INT(3, s.coinChange1(n1, 11));
  EXPECT_EQ_INT(-1, s.coinChange1(n2, 3));
  EXPECT_EQ_INT(0, s.coinChange1(n3, 0));
  EXPECT_EQ_INT(4, s.coinChange1(n4, 18));
  EXPECT_EQ_INT(3, s.coinChange2(n1, 11));
  EXPECT_EQ_INT(-1, s.coinChange2(n2, 3));
  EXPECT_EQ_INT(0, s.coinChange2(n3, 0));
  EXPECT_EQ_INT(4, s.coinChange2(n4, 18));
  EXPECT_EQ_INT(3, s.coinChange3(n1, 11));
  EXPECT_EQ_INT(-1, s.coinChange3(n2, 3));
  EXPECT_EQ_INT(0, s.coinChange3(n3, 0));
  EXPECT_EQ_INT(4, s.coinChange3(n4, 18));
  EXPECT_EQ_INT(3, s.coinChange4(n1, 11));
  EXPECT_EQ_INT(-1, s.coinChange4(n2, 3));
  EXPECT_EQ_INT(0, s.coinChange4(n3, 0));
  EXPECT_EQ_INT(4, s.coinChange4(n4, 18));
  EXPECT_SUMMARY;
}

int main()
{
  testCoinChange();
  return 0;
}
