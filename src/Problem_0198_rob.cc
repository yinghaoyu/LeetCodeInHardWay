#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int f(vector<int>& nums, int index, int money)
  {
    if (index >= nums.size())
    {
      return money;
    }
    int p1 = f(nums, index + 1, money);
    int p2 = f(nums, index + 2, money + nums[index]);
    return std::max(p1, p2);
  }

  int rob(vector<int>& nums) { return f(nums, 0, 0); }

  int dp1(vector<int>& nums)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    if (nums.size() == 1)
    {
      return nums[0];
    }
    int n = nums.size();
    // dp[i] : nums[0...i]范围上可以随意选择数字，但是不能选相邻数，能得到的最大累加和
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);
    for (int i = 2; i < n; i++)
    {
      dp[i] = std::max(dp[i - 1], nums[i] + dp[i - 2]);
    }
    return dp[n - 1];
  }

  // 空间优化
  int dp2(vector<int>& nums)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    if (nums.size() == 1)
    {
      return nums[0];
    }
    int x = nums[0];
    int y = std::max(nums[0], nums[1]);
    for (int i = 2; i < nums.size(); i++)
    {
      int cur = std::max(y, x + nums[i]);
      x = y;
      y = cur;
    }
    return y;
  }
};

void testRob()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 1};
  vector<int> n2 = {2, 7, 9, 3, 1};
  EXPECT_EQ_INT(4, s.rob(n1));
  EXPECT_EQ_INT(12, s.rob(n2));
  EXPECT_EQ_INT(4, s.dp1(n1));
  EXPECT_EQ_INT(12, s.dp1(n2));
  EXPECT_EQ_INT(4, s.dp2(n1));
  EXPECT_EQ_INT(12, s.dp2(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testRob();
  return 0;
}
