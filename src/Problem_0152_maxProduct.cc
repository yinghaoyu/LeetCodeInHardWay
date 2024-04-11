#include <vector>

#include "UnitTest.h"

using namespace std;
// @sa https://www.bilibili.com/video/BV1qu4y187Xn/
// https://leetcode.cn/problems/maximum-product-subarray/solution/dong-tai-gui-hua-li-jie-wu-hou-xiao-xing-by-liweiw/
class Solution
{
 public:
  // 动态规划
  int maxProduct1(vector<int>& nums)
  {
    int n = nums.size();
    // dp[i][0] 表示必须以nums[i]结尾的子数组的最小值
    // dp[i][1] 表示必须以nums[i]结尾的子数组的最大值
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = nums[0];
    dp[0][1] = nums[0];
    for (int i = 1; i < n; i++)
    {
      if (nums[i] < 0)
      {
        dp[i][0] = std::min(dp[i - 1][1] * nums[i], nums[i]);
        dp[i][1] = std::max(dp[i - 1][0] * nums[i], nums[i]);
      }
      else
      {
        dp[i][0] = std::min(dp[i - 1][0] * nums[i], nums[i]);
        dp[i][1] = std::max(dp[i - 1][1] * nums[i], nums[i]);
      }
    }
    int ans = dp[0][1];
    for (int i = 0; i < n; i++)
    {
      ans = std::max(ans, dp[i][1]);
    }
    return ans;
  }

  int maxProduct2(vector<int>& nums)
  {
    int ans = nums[0];
    int preMin = nums[0];
    int preMax = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
      int curMin = std::min(nums[i], std::min(preMin * nums[i], preMax * nums[i]));
      int curMax = std::max(nums[i], std::max(preMin * nums[i], preMax * nums[i]));
      preMin = curMin;
      preMax = curMax;
      ans = std::max(ans, curMax);
    }
    return ans;
  }
};

void testMaxProduct()
{
  Solution s;
  vector<int> n1 = {2, 3, -2, 4};
  vector<int> n2 = {-2, 0, -1};
  vector<int> n3 = {0, 2};
  vector<int> n4 = {-2, 5, -3};
  EXPECT_EQ_INT(6, s.maxProduct1(n1));
  EXPECT_EQ_INT(0, s.maxProduct1(n2));
  EXPECT_EQ_INT(2, s.maxProduct1(n3));
  EXPECT_EQ_INT(30, s.maxProduct1(n4));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxProduct();
  return 0;
}
