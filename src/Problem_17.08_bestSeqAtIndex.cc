#include <algorithm>
#include <vector>

using namespace std;

// @sa Problem_08.13_pileBox.cc
class Solution
{
 public:
  // 超时
  int bestSeqAtIndex(vector<int>& height, vector<int>& weight)
  {
    int n = height.size();
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
    {
      idx[i] = i;
    }
    std::sort(idx.begin(), idx.end(), [&](int i, int j) { return height[i] < height[j]; });
    // dp[i]的含义为，必须以为结尾，最长上升子序列
    vector<int> dp(n);
    dp[idx[0]] = 1;
    int ans = dp[idx[0]];
    for (int i = 1; i < n; i++)
    {
      dp[idx[i]] = 1;
      for (int j = 0; j < i; j++)
      {
        if (height[idx[j]] < height[idx[i]] && weight[idx[j]] < weight[idx[i]])
        {
          dp[idx[i]] = std::max(dp[idx[i]], dp[idx[j]] + 1);
        }
      }
      ans = std::max(ans, dp[idx[i]]);
    }
    return ans;
  }

  // TODO: 贪心
};
