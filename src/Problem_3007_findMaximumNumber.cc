#include <vector>

using namespace std;

class Solution
{
 public:
  long long findMaximumNumber(long long k, int x)
  {
    long long left = 0;
    long long right = (k + 1) << x;
    while (left + 1 < right)
    {
      long long mid = (right - left) / 2 + left;
      if (check(mid, k, x))
      {
        left = mid;
      }
      else
      {
        right = mid;
      }
    }
    return left;
  }

  bool check(long long num, long long k, int x)
  {
    int m = __lg(num) + 1;
    vector<vector<long long>> dp(m, vector<long long>(m + 1, -1));
    return f(m - 1, 0, true, x, num, dp) <= k;
  }

  // 数位 dp
  long long f(int i, int cnt, bool limited, int x, long long num, vector<vector<long long>>& dp)
  {
    if (i < 0)
    {
      return cnt;
    }
    if (!limited && dp[i][cnt] != -1)
    {
      return dp[i][cnt];
    }
    int up = limited ? ((num >> i) & 1) : 1;
    long long ans = 0;
    for (int d = 0; d <= up; d++)
    {
      // 在 d==1 时判断当前下标是否为 x 的倍数
      ans += f(i - 1, cnt + (d == 1 && (i + 1) % x == 0), limited && d == up, x, num, dp);
    }
    if (!limited)
    {
      dp[i][cnt] = ans;
    }
    return ans;
  }
};
