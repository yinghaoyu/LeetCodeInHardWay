#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minCostClimbingStairs(vector<int> &cost)
  {
    int n = cost.size();
    vector<int> dp(n + 1);
    dp[0] = dp[1] = 0;
    for (int i = 2; i <= n; i++)
    {
      dp[i] = std::min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp[n];
  }
};

void test()
{
  Solution s;
  vector<int> c1 = {10, 15, 20};
  vector<int> c2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
  EXPECT_EQ_INT(15, s.minCostClimbingStairs(c1));
  EXPECT_EQ_INT(6, s.minCostClimbingStairs(c2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
