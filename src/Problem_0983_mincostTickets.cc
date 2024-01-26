#include <cstdint>
#include <vector>

using namespace std;

class Solution
{
  vector<int> durations = {1, 7, 30};

 public:
  // 暴力尝试
  int mincostTickets1(vector<int>& days, vector<int>& costs) { return f1(days, costs, 0); }

  // days[i..... 最少花费是多少
  int f1(vector<int>& days, vector<int>& costs, int i)
  {
    if (i == days.size())
    {
      // 后续已经无旅行了
      return 0;
    }
    // i下标 : 第days[i]天，有一场旅行
    // i.... 最少花费是多少
    int ans = INT32_MAX;
    for (int k = 0, j = i; k < durations.size(); k++)
    {
      // k是方案编号 : 0 1 2
      while (j < days.size() && days[i] + durations[k] > days[j])
      {
        // 因为方案2持续的天数最多，30天
        // 所以while循环最多执行30次
        // 枚举行为可以认为是O(1)
        j++;
      }
      ans = std::min(ans, costs[k] + f1(days, costs, j));
    }
    return ans;
  }

  // 暴力尝试改记忆化搜索
  int mincostTickets2(vector<int>& days, vector<int>& costs)
  {
    vector<int> dp(days.size(), INT32_MAX);
    return f2(days, costs, 0, dp);
  }

  int f2(vector<int>& days, vector<int>& costs, int i, vector<int>& dp)
  {
    if (i == days.size())
    {
      return 0;
    }
    if (dp[i] != INT32_MAX)
    {
      return dp[i];
    }
    int ans = INT32_MAX;
    for (int k = 0, j = i; k < durations.size(); k++)
    {
      while (j < days.size() && days[i] + durations[k] > days[j])
      {
        j++;
      }
      ans = std::min(ans, costs[k] + f2(days, costs, j, dp));
    }
    dp[i] = ans;
    return ans;
  }

  // 动态规划
  int mincostTickets3(vector<int>& days, vector<int>& costs)
  {
    int n = days.size();
    vector<int> dp(n + 1, INT32_MAX);
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      for (int k = 0, j = i; k < durations.size(); k++)
      {
        while (j < days.size() && days[i] + durations[k] > days[j])
        {
          j++;
        }
        dp[i] = std::min(dp[i], costs[k] + dp[j]);
      }
    }
    return dp[0];
  }
};
