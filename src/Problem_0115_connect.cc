#include <string>
#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV1cg4y1o719/
class Solution
{
 public:
  int numDistinct1(string s, string t)
  {
    int n = s.length();
    int m = t.length();
    if (n < m)
    {
      return 0;
    }
    // dp[i][j]表示：
    // s[前缀长度为i]的所有子序列中，有多少个等于t[前缀长度为j]
    vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1));
    for (int i = 0; i <= n; i++)
    {
      // 只有空字符串满足条件
      dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        // s[i-1] != t[j-1]
        dp[i][j] = dp[i - 1][j];
        if (s[i - 1] == t[j - 1])
        {
          dp[i][j] += dp[i - 1][j - 1];
        }
      }
    }
    return dp[n][m];
  }

  // 空间压缩
  int numDistinct2(string s, string t)
  {
    int n = s.length();
    int m = t.length();
    if (n < m)
    {
      return 0;
    }
    vector<unsigned long long> dp(m + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
    {
      for (int j = m; j >= 1; j--)
      {
        if (s[i - 1] == t[j - 1])
        {
          dp[j] += dp[j - 1];
        }
      }
    }
    return dp[m];
  }
};
