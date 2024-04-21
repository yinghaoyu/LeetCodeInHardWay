#include <vector>

using namespace std;

// 区间dp
// @sa https://www.bilibili.com/video/BV1NQ4y1b7Uo/
class Solution
{
 public:
  // 记忆化搜索
  int maxCoins1(vector<int>& nums)
  {
    int n = nums.size();
    // a b c d e
    // 1 a b c d e 1
    vector<int> arr(n + 2);
    arr[0] = 1;
    arr[n + 1] = 1;
    for (int i = 0; i < n; i++)
    {
      arr[i + 1] = nums[i];
    }
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
    return f(arr, 1, n, dp);
  }

  // arr[l...r]这些气球决定一个顺序，获得最大得分返回！
  // 一定有 : arr[l-1]一定没爆！
  // 一定有 : arr[r+1]一定没爆！
  // 尝试每个气球最后打爆
  int f(vector<int>& arr, int l, int r, vector<vector<int>>& dp)
  {
    if (dp[l][r] != -1)
    {
      return dp[l][r];
    }
    int ans = 0;
    if (l == r)
    {
      ans = arr[l - 1] * arr[l] * arr[r + 1];
    }
    else
    {
      // l   ....r
      // l +1 +2 .. r
      ans = std::max(arr[l - 1] * arr[l] * arr[r + 1] + f(arr, l + 1, r, dp),   // l 最后打爆
                     arr[l - 1] * arr[r] * arr[r + 1] + f(arr, l, r - 1, dp));  // r 最后打爆
      for (int k = l + 1; k < r; k++)
      {
        // k位置的气球最后打爆
        // l...k-1  k  k+1...r
        ans = std::max(
            ans, arr[l - 1] * arr[k] * arr[r + 1] + f(arr, l, k - 1, dp) + f(arr, k + 1, r, dp));
      }
    }
    dp[l][r] = ans;
    return ans;
  }

  // 动态规划
  int maxCoins2(vector<int>& nums)
  {
    int n = nums.size();
    // a b c d e
    // 1 a b c d e 1
    vector<int> arr(n + 2);
    arr[0] = 1;
    arr[n + 1] = 1;
    for (int i = 0; i < n; i++)
    {
      arr[i + 1] = nums[i];
    }
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
    for (int i = 1; i <= n; i++)
    {
      dp[i][i] = arr[i - 1] * arr[i] * arr[i + 1];
    }
    for (int l = n, ans; l >= 1; l--)
    {
      for (int r = l + 1; r <= n; r++)
      {
        ans = std::max(arr[l - 1] * arr[l] * arr[r + 1] + dp[l + 1][r],
                       arr[l - 1] * arr[r] * arr[r + 1] + dp[l][r - 1]);
        for (int k = l + 1; k < r; k++)
        {
          ans = std::max(ans, arr[l - 1] * arr[k] * arr[r + 1] + dp[l][k - 1] + dp[k + 1][r]);
        }
        dp[l][r] = ans;
      }
    }
    return dp[1][n];
  }
};
