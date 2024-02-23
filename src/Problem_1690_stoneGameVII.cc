#include <vector>

using namespace std;

class Solution
{
 public:
  // Alice尽可能扩大分值差，Bob尽可能缩小分值差
  // 等价于两者都想拿到最大分值差
  int f(vector<int>& sum, int i, int j, vector<vector<int>>& visited)
  {
    if (i >= j)
    {
      return 0;
    }
    if (visited[i][j] != 0)
    {
      return visited[i][j];
    }
    // 先手拿左边，得分sum[j+1] - sum[i+1]，后手拿得到的最大差值 f(sum, i + 1, j , visited)
    // 先手拿右边，得分sum[j] - sum[i]，后手拿得到的最大差值 f(sum, i, j - 1, visited)
    // 先手拿得到的最大差值为，两次尝试的差值最大值
    int ans = std::max(sum[j + 1] - sum[i + 1] - f(sum, i + 1, j, visited),
                       sum[j] - sum[i] - f(sum, i, j - 1, visited));
    visited[i][j] = ans;
    return ans;
  }

  // 记忆化搜索
  int stoneGameVII(vector<int>& stones)
  {
    int n = stones.size();
    vector<int> sum(n + 1);
    vector<vector<int>> visited(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
      sum[i + 1] = sum[i] + stones[i];
    }
    return f(sum, 0, n - 1, visited);
  }

  // 动态规划
  int dp(vector<int>& stones)
  {
    int n = stones.size();
    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++)
    {
      sum[i + 1] = sum[i] + stones[i];
    }
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = n - 2; i >= 0; i--)
    {
      for (int j = i + 1; j < n; j++)
      {
        dp[i][j] =
            std::max(sum[j + 1] - sum[i + 1] - dp[i + 1][j], sum[j - 1] - sum[i] - dp[i][j - 1]);
      }
    }
    return dp[0][n - 1];
  }
};
