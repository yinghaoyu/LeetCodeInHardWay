#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int strangePrinter(string s)
  {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n));
    dp[n - 1][n - 1] = 1;
    for (int i = 0; i < n - 1; i++)
    {
      // 只有1个字符，打印1次
      dp[i][i] = 1;
      // 2个字符不同，需打印2次
      dp[i][i + 1] = s[i] == s[i + 1] ? 1 : 2;
    }
    for (int l = n - 3, ans; l >= 0; l--)
    {
      for (int r = l + 2; r < n; r++)
      {
        // dp[l][r]
        if (s[l] == s[r])
        {
          dp[l][r] = dp[l][r - 1];
          // dp[l][r] = dp[l + 1][r];
        }
        else
        {
          ans = INT32_MAX;
          for (int m = l; m < r; m++)
          {
            ans = std::min(ans, dp[l][m] + dp[m + 1][r]);
          }
          dp[l][r] = ans;
        }
      }
    }
    return dp[0][n - 1];
  }
};
