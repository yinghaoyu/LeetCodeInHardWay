#include <stdint.h>
#include <vector>

using namespace std;

class Solution
{
 public:
 public:
  int f(vector<int>& cost, vector<int>& time, int i, int j, vector<vector<int>>& dp)
  {
    if (j > i)
    {
      // 说明时长足够，完全可以用免费的油漆匠
      return 0;
    }
    if (i < 0)
    {
      // i < 0 且 j <= i，说明 j < 0
      // 明显不符合
      return INT32_MAX;
    }
    // i 的最小值可能是 -n，平移到数组的有效范围
    if (dp[i][j + cost.size()] != -1)
    {
      return dp[i][j + cost.size()];
    }
    int p1 = f(cost, time, i - 1, j + time[i], dp);
    if (p1 != INT32_MAX)
    {
      p1 += cost[i];
    }
    int p2 = f(cost, time, i - 1, j - 1, dp);
    dp[i][j + cost.size()] = std::min(p1, p2);
    return dp[i][j + cost.size()];
  }

  int paintWalls(vector<int>& cost, vector<int>& time)
  {
    int n = cost.size();
    vector<vector<int>> dp(n, vector<int>(2 * n + 1, -1));
    return f(cost, time, n - 1, 0, dp);
  }
};
