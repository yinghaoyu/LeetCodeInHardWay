#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxProfit1(int k, vector<int> &prices)
  {
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2)));
    for (int i = 1; i < k + 1; i++)
    {
      dp[0][i][1] = -prices[0];
    }
    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j < k + 1; j++)
      {
        dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
        dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
      }
    }
    return dp[n - 1][k][0];
  }

  // TODO: figure it out
  int maxProfit2(int k, vector<int> &prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int n = prices.size();
    if (k >= n / 2)
    {
      return allTrans(prices);
    }
    vector<vector<int>> dp(n, vector<int>(k + 1));
    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j < k + 1; j++)
      {
        dp[i][j] = dp[i - 1][j];
        for (int p = 0; p <= i; p++)
        {
          dp[i][j] = std::max(dp[p][j - 1] + prices[i] - prices[p], dp[i][j]);
        }
      }
    }
    return dp[n - 1][k];
  }

  int allTrans(vector<int> &prices)
  {
    int ans = 0;
    for (int i = 1; i < prices.size(); i++)
    {
      ans += std::max(prices[i] - prices[i - 1], 0);
    }
    return ans;
  }

  int maxProfit3(int k, vector<int> &prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int n = prices.size();
    if (k >= n / 2)
    {
      return allTrans(prices);
    }
    vector<vector<int>> dp(n, vector<int>(k + 1));
    int ans = 0;
    for (int j = 1; j <= k; j++)
    {
      int pre = dp[j][0];
      int best = pre - prices[0];
      for (int i = 1; i < n; i++)
      {
        pre = dp[j - 1][i];
        dp[j][i] = std::max(dp[j][i - 1], prices[i] + best);
        best = std::max(best, pre - prices[i]);
        ans = std::max(dp[j][i], ans);
      }
    }
    return ans;
  }
};

void testMaxProfit()
{
  Solution s;
  vector<int> p1 = {2, 4, 1};
  vector<int> p2 = {3, 2, 6, 5, 0, 3};
  EXPECT_EQ_INT(2, s.maxProfit1(2, p1));
  EXPECT_EQ_INT(7, s.maxProfit1(2, p2));
  EXPECT_EQ_INT(2, s.maxProfit2(2, p1));
  EXPECT_EQ_INT(7, s.maxProfit2(2, p2));
  EXPECT_EQ_INT(2, s.maxProfit3(2, p1));
  EXPECT_EQ_INT(7, s.maxProfit3(2, p2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxProfit();
  return 0;
}
