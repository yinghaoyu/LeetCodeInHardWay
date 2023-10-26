#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numRollsToTarget(int n, int k, int target)
  {
    const int mod = 1e9 + 7;
    vector<vector<int>> dp(n + 1, vector<int>(target + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= target; j++)
      {
        for (int x = 1; x <= k; x++)
        {
          if (j - x >= 0)
          {
            dp[i][j] = (dp[i][j] + dp[i - 1][j - x]) % mod;
          }
        }
      }
    }
    return dp[n][target];
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(1, s.numRollsToTarget(1, 6, 3));
  EXPECT_EQ_INT(6, s.numRollsToTarget(2, 6, 7));
  EXPECT_EQ_INT(222616187, s.numRollsToTarget(30, 30, 500));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
