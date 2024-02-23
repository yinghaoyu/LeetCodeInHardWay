#include <string>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/interleaving-string/
// @sa Problem_0097_isInterleave.cc
class Solution
{
 public:
  bool isInterleave(string s1, string s2, string s3)
  {
    if (s1.length() + s2.length() != s3.length())
    {
      return false;
    }
    int n = s1.length();
    int m = s2.length();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
    {
      if (s1[i - 1] != s3[i - 1])
      {
        break;
      }
      dp[i][0] = true;
    }
    for (int j = 1; j <= m; j++)
    {
      if (s2[j - 1] != s3[j - 1])
      {
        break;
      }
      dp[0][j] = true;
    }
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        dp[i][j] = (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) ||
                   (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
      }
    }
    return dp[n][m];
  }
};
