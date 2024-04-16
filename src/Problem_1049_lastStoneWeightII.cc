#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV1NN41137jF/
class Solution
{
 public:
  // 转化成 01 背包问题
  int lastStoneWeightII(vector<int>& stones)
  {
    int sum = 0;
    for (int num : stones)
    {
      sum += num;
    }
    // nums中随意选择数字
    // 累加和一定要 <= sum / 2
    // 又尽量接近
    int ret = near(stones, sum / 2);
    // 另一个集合 sum - ret
    // 返回两个集合之差即为答案
    return sum - ret - ret;
  }

  // 非负数组nums中，子序列累加和不超过t，但是最接近t的累加和是多少
  // 01背包问题(子集累加和尽量接近t) + 空间压缩
  int near(vector<int>& nums, int t)
  {
    vector<int> dp(t + 1);
    for (int num : nums)
    {
      for (int j = t; j >= num; j--)
      {
        // dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-nums[i]]+nums[i])
        dp[j] = std::max(dp[j], dp[j - num] + num);
      }
    }
    return dp[t];
  }
};
