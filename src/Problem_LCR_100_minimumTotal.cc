#include <algorithm>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/triangle/
// @sa Problem_0064_minPathSum.cc
class Solution
{
 public:
  int minimumTotal(vector<vector<int>>& triangle)
  {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n));
    // base case
    // 第 0 行只有一个元素
    dp[0][0] = triangle[0][0];
    for (int i = 1; i < n; i++)
    {
      // 第 i 行有 i + 1 个元素

      // 最左侧时，只能从上一行的最左侧转移而来
      dp[i][0] = dp[i - 1][0] + triangle[i][0];
      for (int j = 1; j < i; j++)
      {
        dp[i][j] = std::min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
      }
      // 最右侧时，只能从上一行的最右侧转移而来
      dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }
    // 取最后一行的最小值
    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
  }
};
