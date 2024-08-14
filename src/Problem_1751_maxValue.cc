#include <algorithm>
#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  // events[i][0] : 开始时间
  // events[i][1] : 结束时间
  // events[i][2] : 收益
  int maxValue(vector<vector<int>>& events, int k)
  {
    int n = events.size();
    std::sort(events.begin(), events.end(),
              [](vector<int>& l, vector<int>& r) { return l[1] < r[1]; });
    // dp[i][j] : 0..i范围上最多选j个会议召开，最大收益是多少
    vector<vector<int>> dp(n, vector<int>(k + 1));
    for (int j = 1; j <= k; j++)
    {
      dp[0][j] = events[0][2];
    }
    for (int i = 1, pre; i < n; i++)
    {
      pre = find(events, i - 1, events[i][0]);
      for (int j = 1; j <= k; j++)
      {
        dp[i][j] = std::max(dp[i - 1][j], (pre == -1 ? 0 : dp[pre][j - 1]) + events[i][2]);
      }
    }
    return dp[n - 1][k];
  }

  // 0...i范围上的会议，根据结束日期排序了
  // 找到结束时间<s，最右的会议编号
  // 如果不存在这样的会议返回-1
  int find(vector<vector<int>>& events, int i, int s)
  {
    int l = 0;
    int r = i;
    int ans = -1;
    while (l <= r)
    {
      int mid = (l + r) / 2;
      if (events[mid][1] < s)
      {
        ans = mid;
        l = mid + 1;
      }
      else
      {
        r = mid - 1;
      }
    }
    return ans;
  }
};
