#include <string>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/distinct-subsequences/
// @sa Problem_0115_connect.cc
class Solution
{
 public:
  int numDistinct(string s, string t)
  {
    int n = s.length();
    int m = t.length();
    if (n < m)
    {
      return 0;
    }
    // dp[i][j]的含义为：
    // s[前缀长度i]有多少个t[前缀长度j]的子串
    vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1));
    for (int i = 0; i <= n; i++)
    {
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
};
