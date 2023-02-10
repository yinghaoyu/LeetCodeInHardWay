#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int dp1(int n, vector<int> &rollMax)
  {
    static const int mod = 1e9 + 7;
    // dp[i][j][k]的含义为：
    // 完成i次掷骰子，第i次掷的是j，并且已经连续掷了k次j的合法序列数
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(6, vector<int>(16)));
    for (int j = 0; j < 6; j++)
    {
      dp[1][j][1] = 1;
    }
    for (int i = 2; i <= n; i++)
    {
      for (int j = 0; j < 6; j++)
      {
        for (int k = 1; k <= rollMax[j]; k++)
        {
          for (int p = 0; p < 6; p++)
          {
            if (p != j)
            {
              // 当前掷的数p ！= 上次掷的数j
              dp[i][p][1] = (dp[i][p][1] + dp[i - 1][j][k]) % mod;
            }
            else if (k + 1 <= rollMax[j])
            {
              // 当前掷的数p == 上次掷的数j 并且当前掷的数p的连续次数 k + 1 <= 规定范围 rollMax[j]
              dp[i][p][k + 1] = (dp[i][p][k + 1] + dp[i - 1][j][k]) % mod;
            }
          }
        }
      }
    }
    int ans = 0;
    for (int j = 0; j < 6; j++)
    {
      for (int k = 1; k <= rollMax[j]; k++)
      {
        ans = (ans + dp[n][j][k]) % mod;
      }
    }
    return ans;
  }

  // 空间优化
  // 根据dp1，发现dp[i]只跟dp[i-1]状态有关
  int dp2(int n, vector<int> &rollMax)
  {
    static const int mod = 1e9 + 7;
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(6, vector<int>(16)));
    for (int j = 0; j < 6; j++)
    {
      dp[1][j][1] = 1;
    }
    for (int i = 2; i <= n; i++)
    {
      // 缩减为奇数、偶数
      int t = i & 1;
      for (int j = 0; j < 6; j++)
      {
        std::fill(dp[t][j].begin(), dp[t][j].end(), 0);
      }
      for (int j = 0; j < 6; j++)
      {
        for (int k = 1; k <= rollMax[j]; k++)
        {
          for (int p = 0; p < 6; p++)
          {
            if (p != j)
            {
              dp[t][p][1] = (dp[t][p][1] + dp[t ^ 1][j][k]) % mod;
            }
            else if (k + 1 <= rollMax[j])
            {
              dp[t][p][k + 1] = (dp[t][p][k + 1] + dp[t ^ 1][j][k]) % mod;
            }
          }
        }
      }
    }

    int ans = 0;
    for (int j = 0; j < 6; j++)
    {
      for (int k = 1; k <= rollMax[j]; k++)
      {
        ans = (ans + dp[n & 1][j][k]) % mod;
      }
    }
    return ans;
  }

  int dp3(int n, vector<int> &rollMax)
  {
    // TODO: 状态优化
  }

  int dieSimulator(int n, vector<int> &rollMax)
  {
    int ans1 = dp1(n, rollMax);
    int ans2 = dp2(n, rollMax);
    return ans1 == ans2 ? ans1 : 0;
  }
};

void testDieSimulator()
{
  Solution s;
  vector<int> r1 = {1, 1, 2, 2, 2, 3};
  vector<int> r2 = {1, 1, 1, 1, 1, 1};
  vector<int> r3 = {1, 1, 1, 2, 2, 3};
  vector<int> r4 = {2, 7, 1, 2, 6, 5};
  EXPECT_EQ_INT(34, s.dieSimulator(2, r1));
  EXPECT_EQ_INT(30, s.dieSimulator(2, r2));
  EXPECT_EQ_INT(181, s.dieSimulator(3, r3));
  EXPECT_EQ_INT(45008937, s.dieSimulator(10, r4));
  EXPECT_SUMMARY;
}

int main()
{
  testDieSimulator();
  return 0;
}
