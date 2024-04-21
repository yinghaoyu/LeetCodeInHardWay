#include <cstdint>
#include <vector>

using namespace std;

// 区间dp
// @sa https://www.bilibili.com/video/BV1NQ4y1b7Uo/
class Solution
{
 public:
  // 记忆化搜索
  int minScoreTriangulation(vector<int>& values)
  {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return f(values, 0, n - 1, dp);
  }

  // 根据划分点来做可能性展开
  int f(vector<int>& arr, int l, int r, vector<vector<int>>& dp)
  {
    if (dp[l][r] != -1)
    {
      return dp[l][r];
    }
    int ans = INT32_MAX;
    if (l == r || l == r - 1)
    {
      // 只有一个顶点或者两个顶点
      // 明显不能组成三角形
      ans = 0;
    }
    else
    {
      // 有 3 个及以上顶点，枚举顶点arr[m]，其中arr[l]、arr[r]作为左右点
      // l....r >=3
      // 0..1..2..3..4...5
      for (int m = l + 1; m < r; m++)
      {
        // l m r
        // 左右分别去划分
        ans = std::min(ans, f(arr, l, m, dp) + f(arr, m, r, dp) + arr[l] * arr[m] * arr[r]);
      }
    }
    dp[l][r] = ans;
    return ans;
  }

  int minScoreTriangulation2(vector<int>& arr)
  {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int l = n - 3; l >= 0; l--)
    {
      for (int r = l + 2; r < n; r++)
      {
        dp[l][r] = INT32_MAX;
        for (int m = l + 1; m < r; m++)
        {
          dp[l][r] = std::min(dp[l][r], dp[l][m] + dp[m][r] + arr[l] * arr[m] * arr[r]);
        }
      }
    }
    return dp[0][n - 1];
  }
};
