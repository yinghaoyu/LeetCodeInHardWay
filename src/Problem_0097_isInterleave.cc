#include <string>
#include <vector>

using namespace std;

// 交错字符串
// 给定三个字符串 s1、s2、s3
// 请帮忙验证s3是否由s1和s2交错组成

// @sa https://www.bilibili.com/video/BV1cg4y1o719/
class Solution
{
 public:
  bool isInterleave1(string s1, string s2, string s3)
  {
    if (s1.length() + s2.length() != s3.length())
    {
      return false;
    }
    int n = s1.length();
    int m = s2.length();
    // dp[i][j]:
    // s1[前缀长度为i]和s2[前缀长度为j]，能否交错组成出s3[前缀长度为i+j]
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
    dp[0][0] = true;
    // 只有 s1
    for (int i = 1; i <= n; i++)
    {
      if (s1[i - 1] != s3[i - 1])
      {
        break;
      }
      dp[i][0] = true;
    }
    // 只有 s2
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
        // 如果 s1[i-1] == s3[i+j-1]，说明这个字符由 s1 提供，
        // 同时s1[i-1前缀长度]和s2[j前缀长度]能交错组成s3[i+j-1前缀长度]，即dp[i-1][j] = true，
        // 则dp[i][j]也满足条件。s2同理
        dp[i][j] = (s1[i - 1] == s3[i + j - 1] && dp[i - 1][j]) ||
                   (s2[j - 1] == s3[i + j - 1] && dp[i][j - 1]);
      }
    }
    return dp[n][m];
  }

  // 空间压缩
  bool isInterleave2(string s1, string s2, string s3)
  {
    if (s1.length() + s2.length() != s3.length())
    {
      return false;
    }
    int n = s1.length();
    int m = s2.length();
    vector<bool> dp(m + 1);
    dp[0] = true;
    for (int j = 1; j <= m; j++)
    {
      if (s2[j - 1] != s3[j - 1])
      {
        break;
      }
      dp[j] = true;
    }
    for (int i = 1; i <= n; i++)
    {
      dp[0] = s1[i - 1] == s3[i - 1] && dp[0];
      for (int j = 1; j <= m; j++)
      {
        dp[j] = (s1[i - 1] == s3[i + j - 1] && dp[j]) || (s2[j - 1] == s3[i + j - 1] && dp[j - 1]);
      }
    }
    return dp[m];
  }
};
