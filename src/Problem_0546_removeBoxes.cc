#include <vector>

using namespace std;

// 区间dp
// @sa https://www.bilibili.com/video/BV1du4y1L7gy/
class Solution
{
 public:
  // 时间复杂度O(n^4)
  int removeBoxes(vector<int>& boxes)
  {
    int n = boxes.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));
    return f(boxes, 0, n - 1, 0, dp);
  }

  // boxes[l....r]范围上要去消除，前面跟着k个连续的和boxes[l]颜色一样的盒子
  // 这种情况下，返回最大得分
  int f(vector<int>& boxes, int l, int r, int k, vector<vector<vector<int>>>& dp)
  {
    if (l > r)
    {
      return 0;
    }
    // l <= r
    if (dp[l][r][k] > 0)
    {
      return dp[l][r][k];
    }
    int s = l;
    while (s + 1 <= r && boxes[l] == boxes[s + 1])
    {
      s++;
    }
    // boxes[l...s]都是一种颜色，boxes[s+1]就不是同一种颜色了
    // cnt是总前缀数量 : 之前的相同前缀(k个) + l...s这个颜色相同的部分(s-l+1个)
    int cnt = k + s - l + 1;
    // 可能性1 : 前缀先消
    int ans = cnt * cnt + f(boxes, s + 1, r, 0, dp);
    // 可能性2 : 讨论前缀跟着哪个后，一起消掉
    for (int m = s + 2; m <= r; m++)
    {
      if (boxes[l] == boxes[m] && boxes[m - 1] != boxes[m])
      {
        // boxes[l] == boxes[m]是必须条件
        // boxes[m - 1] != boxes[m]是剪枝条件，避免不必要的调用
        ans = std::max(ans, f(boxes, s + 1, m - 1, 0, dp) + f(boxes, m, r, cnt, dp));
      }
    }
    dp[l][r][k] = ans;
    return ans;
  }
};
