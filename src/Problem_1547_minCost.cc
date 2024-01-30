#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 记忆化搜索
  int minCost1(int n, vector<int>& cuts)
  {
    int m = cuts.size();
    std::sort(cuts.begin(), cuts.end());
    vector<int> arr(m + 2);
    arr[0] = 0;
    for (int i = 1; i <= m; i++)
    {
      arr[i] = cuts[i - 1];
    }
    arr[m + 1] = n;
    vector<vector<int>> dp(m + 2, vector<int>(m + 2, -1));
    return f(arr, 1, m, dp);
  }

  // 切点[l....r]，决定一个顺序
  // 让切点都切完，总代价最小
  int f(vector<int>& arr, int l, int r, vector<vector<int>>& dp)
  {
    if (l > r)
    {
      return 0;
    }
    if (l == r)
    {
      return arr[r + 1] - arr[l - 1];
    }
    if (dp[l][r] != -1)
    {
      return dp[l][r];
    }
    int ans = INT32_MAX;
    for (int k = l; k <= r; k++)
    {
      ans = std::min(ans, f(arr, l, k - 1, dp) + f(arr, k + 1, r, dp));
    }
    ans += arr[r + 1] - arr[l - 1];
    dp[l][r] = ans;
    return ans;
  }

  // 动态规划
  int minCost2(int n, vector<int>& cuts)
  {
    int m = cuts.size();
    std::sort(cuts.begin(), cuts.end());
    vector<int> arr(m + 2);
    arr[0] = 0;
    for (int i = 1; i <= m; i++)
    {
      arr[i] = cuts[i - 1];
    }
    arr[m + 1] = n;
    vector<vector<int>> dp(m + 2, vector<int>(m + 2));
    for (int i = 1; i <= m; i++)
    {
      dp[i][i] = arr[i + 1] - arr[i - 1];
    }
    for (int l = m - 1, next; l >= 1; l--)
    {
      for (int r = l + 1; r <= m; r++)
      {
        next = INT32_MAX;
        for (int k = l; k <= r; k++)
        {
          next = std::min(next, dp[l][k - 1] + dp[k + 1][r]);
        }
        dp[l][r] = arr[r + 1] - arr[l - 1] + next;
      }
    }
    return dp[1][m];
  }
};
