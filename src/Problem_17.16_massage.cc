#include <vector>

using namespace std;

class Solution
{
 public:
  int massage(vector<int>& nums)
  {
    int n = nums.size();
    if (n == 0)
    {
      return 0;
    }
    // dp[i][0] 表示考虑前 i 个预约，第 i 个预约不接的最长预约时间
    // dp[i][1] 表示考虑前 i 个预约，第 i 个预约接的最长预约时间

    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = nums[0];
    for (int i = 1; i < n; i++)
    {
      // 第 i 个不预约，那么第 i - 1 个可预约，也可不预约，取最大值
      dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1]);
      // 第 i 个预约，那么第 i - 1 个一定不能预约
      dp[i][1] = dp[i - 1][0] + nums[i];
      // 考虑到这里dp[i][0/1]只与dp[i-1][0/1]有关，因此可以用两个变量空间优化
    }
    return std::max(dp[n - 1][0], dp[n - 1][1]);
  }
};
