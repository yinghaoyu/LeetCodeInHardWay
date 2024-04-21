#include <vector>

using namespace std;

// 区间dp
// @sa https://www.bilibili.com/video/BV1NQ4y1b7Uo/
class Solution
{
 public:
  // 暴力尝试
  bool predictTheWinner1(vector<int>& nums)
  {
    int sum = 0;
    for (int num : nums)
    {
      sum += num;
    }
    int n = nums.size();
    int first = f1(nums, 0, n - 1);
    int second = sum - first;
    return first >= second;
  }

  // nums[l...r]范围上的数字进行游戏，轮到玩家1
  // 返回玩家1最终能获得多少分数，玩家1和玩家2都绝顶聪明
  int f1(vector<int>& nums, int l, int r)
  {
    if (l == r)
    {
      return nums[l];
    }
    if (l == r - 1)
    {
      return std::max(nums[l], nums[r]);
    }
    // l....r 不只两个数
    // 可能性1 ：玩家1拿走nums[l] l+1...r
    //           玩家2可能拿走nums[l+1]或者nums[r]，玩家1后续只能拿更小的
    int p1 = nums[l] + std::min(f1(nums, l + 2, r), f1(nums, l + 1, r - 1));
    // 可能性2 ：玩家1拿走nums[r] l...r-1
    //           玩家2可能拿走nums[l]或者nums[r-1]，玩家1后续只能拿更小的
    int p2 = nums[r] + std::min(f1(nums, l + 1, r - 1), f1(nums, l, r - 2));
    return std::max(p1, p2);
  }

  // 记忆化搜索
  bool predictTheWinner2(vector<int>& nums)
  {
    int sum = 0;
    for (int num : nums)
    {
      sum += num;
    }
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    int first = f2(nums, 0, n - 1, dp);
    int second = sum - first;
    return first >= second;
  }

  int f2(vector<int>& nums, int l, int r, vector<vector<int>>& dp)
  {
    if (dp[l][r] != -1)
    {
      return dp[l][r];
    }
    int ans = 0;
    if (l == r)
    {
      ans = nums[l];
    }
    else if (l == r - 1)
    {
      ans = std::max(nums[l], nums[r]);
    }
    else
    {
      int p1 = nums[l] + std::min(f2(nums, l + 2, r, dp), f2(nums, l + 1, r - 1, dp));
      int p2 = nums[r] + std::min(f2(nums, l + 1, r - 1, dp), f2(nums, l, r - 2, dp));
      ans = std::max(p1, p2);
    }
    dp[l][r] = ans;
    return ans;
  }

  // 动态规划
  bool predictTheWinner3(vector<int>& nums)
  {
    int sum = 0;
    for (int num : nums)
    {
      sum += num;
    }
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n - 1; i++)
    {
      dp[i][i] = nums[i];
      dp[i][i + 1] = std::max(nums[i], nums[i + 1]);
    }
    dp[n - 1][n - 1] = nums[n - 1];
    for (int l = n - 3; l >= 0; l--)
    {
      for (int r = l + 2; r < n; r++)
      {
        dp[l][r] = std::max(nums[l] + std::min(dp[l + 2][r], dp[l + 1][r - 1]),
                            nums[r] + std::min(dp[l + 1][r - 1], dp[l][r - 2]));
      }
    }
    int first = dp[0][n - 1];
    int second = sum - first;
    return first >= second;
  }
};
