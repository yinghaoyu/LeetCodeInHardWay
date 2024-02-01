#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxProfit(vector<int>& prices, int fee)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    // 如果需要在买入时扣除手续费，则要修改 dp[0][1]
    // dp[0][1] = -prices[0] - fee
    for (int i = 1; i < n; i++)
    {
      // 思考：为什么不可以在买入股票时扣除手续费？
      dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
      dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
      // dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
    }
    return dp[n - 1][0];
  }
};

void test()
{
  Solution s;
  vector<int> p1 = {1, 3, 2, 8, 4, 9};
  vector<int> p2 = {1, 3, 7, 5, 10, 3};
  EXPECT_EQ_INT(8, s.maxProfit(p1, 2));
  EXPECT_EQ_INT(6, s.maxProfit(p2, 3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
