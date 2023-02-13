#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // '*' 匹配任意长度字符串包括空字符串
  // '?' 匹配任意单个字符
  // s[si...] 能否被 p[pi...] 匹配出来
  bool process(string s, string p, int si, int pi)
  {
    if (si == s.length())
    {
      // s -> ""
      if (pi == p.length())
      {
        // p -> ""
        return true;
      }
      else
      {
        // p -> "..."
        // p[pi] == '*' && p[pi+1...] -> "..."
        return p[pi] == '*' && process(s, p, si, pi + 1);
      }
    }
    if (pi == p.length())
    {
      // p -> ""
      // s -> "..."
      return si == s.length();
    }
    // s 从si出发... p从pi出发
    // s[si] -> 小写字母
    // p[pi] -> 小写字母 或 '?' 或 '*'
    if (p[pi] != '?' && p[pi] != '*')
    {
      return s[si] == p[pi] && process(s, p, si + 1, pi + 1);
    }
    // si... pi... pi ? *
    if (p[pi] == '?')
    {
      return process(s, p, si + 1, pi + 1);
    }
    for (int len = 0; len <= s.length() - si; len++)
    {
      // p[pi] 尝试用 * 去匹配s[si]的后续任意长度
      if (process(s, p, si + len, pi + 1))
      {
        return true;
      }
    }
    return false;
  }

  bool isMatch1(string s, string p) { return process(s, p, 0, 0); }

  // 递归改动态规划
  bool isMatch2(string s, string p)
  {
    int n = s.length();
    int m = p.length();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
    // base case
    // 对应 si == s.length() && pi == p.length()
    // 此时匹配为结束
    dp[n][m] = true;
    for (int pi = m - 1; pi >= 0; pi--)
    {
      // 对应 si == s.length() && pi != p.length()
      // 需要 pi + 1 位置继续往后匹配
      dp[n][pi] = p[pi] == '*' && dp[n][pi + 1];
    }
    for (int si = n - 1; si >= 0; si--)
    {
      for (int pi = m - 1; pi >= 0; pi--)
      {
        if (p[pi] != '?' && p[pi] != '*')
        {
          dp[si][pi] = s[si] == p[pi] && dp[si + 1][pi + 1];
          continue;
        }
        if (p[pi] == '?')
        {
          dp[si][pi] = dp[si + 1][pi + 1];
          continue;
        }
        // p[pi] == '*'
        // dp[si][pi + 1] 表示不用这个 '*'
        // dp[si + 1][pi] 表示用这个 '*'
        dp[si][pi] = dp[si][pi + 1] || dp[si + 1][pi];
      }
    }
    return dp[0][0];
  }

  // 简化版
  bool isMatch3(string s, string p)
  {
    int n = s.length();
    int m = p.length();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
    // base case
    // 对应 si == s.length() && pi == p.length()
    // 此时匹配为结束
    dp[n][m] = true;
    for (int pi = m - 1; pi >= 0; pi--)
    {
      // 对应 si == s.length() && pi != p.length()
      // 需要 pi + 1 位置继续往后匹配
      dp[n][pi] = p[pi] == '*' && dp[n][pi + 1];
    }
    for (int si = n - 1; si >= 0; si--)
    {
      for (int pi = m - 1; pi >= 0; pi--)
      {
        if (p[pi] != '*')
        {
          dp[si][pi] = (p[pi] == '?' || s[si] == p[pi]) && dp[si + 1][pi + 1];
        }
        else
        {
          // p[pi] == '*'
          // dp[si][pi + 1] 表示不用这个 '*'
          // dp[si + 1][pi] 表示用这个 '*'
          dp[si][pi] = dp[si][pi + 1] || dp[si + 1][pi];
        }
      }
    }
    return dp[0][0];
  }
};

void testIsMatch()
{
  Solution s;
  EXPECT_FALSE(s.isMatch1("aa", "a"));
  EXPECT_TRUE(s.isMatch1("aa", "*"));
  EXPECT_FALSE(s.isMatch1("cb", "?a"));
  EXPECT_FALSE(s.isMatch1("bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab", "b*b*ab**ba*b**b***bba"));
  EXPECT_FALSE(s.isMatch2("aa", "a"));
  EXPECT_TRUE(s.isMatch2("aa", "*"));
  EXPECT_FALSE(s.isMatch2("cb", "?a"));
  EXPECT_FALSE(s.isMatch2("bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab", "b*b*ab**ba*b**b***bba"));
  EXPECT_FALSE(s.isMatch3("aa", "a"));
  EXPECT_TRUE(s.isMatch3("aa", "*"));
  EXPECT_FALSE(s.isMatch3("cb", "?a"));
  EXPECT_FALSE(s.isMatch3("bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab", "b*b*ab**ba*b**b***bba"));
  EXPECT_SUMMARY;
}

int main()
{
  testIsMatch();
  return 0;
}
