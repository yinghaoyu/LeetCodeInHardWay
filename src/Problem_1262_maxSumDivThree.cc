#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxSumDivThree(vector<int> &nums)
  {
    int N = nums.size();
    // dp[i][j]表示前i个数选取若干个数，使得这若干个数的和模 3 余 j 的最大值
    // dp[i-1][j] 表示不选
    // dp[i-1][(j - nums[i-1] + 3) % 3] + nums[i-1] 表示选
    vector<vector<int>> dp(N + 1, vector<int>(3));
    dp[0][0] = 0;
    dp[0][1] = INT32_MIN;  // 这里设置为最小值，就算把dp[0][1]纳入计算，得到的值也是最小的
    dp[0][2] = INT32_MIN;
    for (int i = 1; i <= N; ++i)
    {
      int x = nums[i - 1];
      for (int j = 0; j < 3; ++j)
      {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][(j - x % 3 + 3) % 3] + x);
      }
    }
    return dp[N][0];
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {3, 6, 5, 1, 8};
  vector<int> n2 = {4};
  vector<int> n3 = {1, 2, 3, 4, 4};
  EXPECT_EQ_INT(18, s.maxSumDivThree(n1));
  EXPECT_EQ_INT(0, s.maxSumDivThree(n2));
  EXPECT_EQ_INT(12, s.maxSumDivThree(n3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
