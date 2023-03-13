#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 过滤掉无效字符
  bool isValid(string &str, string &pattern)
  {
    for (char &cha : str)
    {
      // str不能有.和*
      if (cha == '.' || cha == '*')
      {
        return false;
      }
    }
    for (int i = 0; i < pattern.length(); i++)
    {
      // *不能在pattern的第一个位置
      // 两个*不能连在一起
      if (pattern[i] == '*' && (i == 0 || pattern[i - 1] == '*'))
      {
        return false;
      }
    }
    return true;
  }

  bool isMatch1(string s, string p)
  {
    if (s.length() == 0 || p.length() == 0)
    {
      return false;
    }
    return isValid(s, p) && process1(s, p, 0, 0);
  }

  // str[i.....] 能否被 pattern[j...] 变出来
  // 潜台词：j位置，pattern[j] != '*'
  bool process1(string &str, string &pattern, int i, int j)
  {
    if (j == pattern.length())
    {
      // j到结尾位置的时候
      // 即：无匹配串的时候，i必须也要到结尾位置才能算匹配，否则不可能匹配上
      return i == str.length();
    }
    // j 没越界
    if (i == str.length())
    {
      // i越界了
      if (j + 1 < pattern.length() && pattern[j + 1] == '*')
      {
        // 后面必须是若干个: 有效字符 + "*" 的组合模式
        // 这样才能让有效字符被*消化成空字符串
        return process1(str, pattern, i, j + 2);
      }
      return false;
    }
    // i 没越界 j 没越界
    if (j + 1 >= pattern.length() || pattern[j + 1] != '*')
    {
      // j到了有效字符的最后一个位置
      // 或者j的下一个位置不是*，则p[j]必须要独立面对s[i]
      return ((str[i] == pattern[j]) || (pattern[j] == '.')) && process1(str, pattern, i + 1, j + 1);
    }
    // pattern[j+1] == '*'
    if (pattern[j] != '.' && str[i] != pattern[j])
    {
      // str[i]和pattern[j]匹配不上
      // 只能把pattern[j]和 pattern[j+1]消为空串
      return process1(str, pattern, i, j + 2);
    }
    // pattern[j+1] == '*' str[i]可配pattern[j]
    // 但是尝试一下消去后能不能匹配
    if (process1(str, pattern, i, j + 2))
    {
      return true;
    }
    // pattern[j+1] == '*'
    while (i < str.length() && (str[i] == pattern[j] || pattern[j] == '.'))
    {
      // 将pattern[j+1]位置上的*衍生出 0 1 2 .. n 个 pattern[j]
      if (process1(str, pattern, i + 1, j + 2))
      {
        return true;
      }
      i++;
    }
    return false;
  }

  bool isMatch2(string s, string p) { return f1(s, p, 0, 0); }

  bool f1(string s, string p, int si, int pi)
  {
    if (pi == p.length())
    {
      return si == s.length();
    }
    if (si == s.length())
    {
      return pi + 1 < p.length() && p[pi + 1] == '*' && f1(s, p, si, pi + 2);
    }
    if (pi + 1 >= p.length() || p[pi + 1] != '*')
    {
      return (s[si] == p[pi] || p[pi] == '.') && f1(s, p, si + 1, pi + 1);
    }
    // p[pi+1] == '*'
    // a) 就是让[pi, pi+1]变空
    bool ans = f1(s, p, si, pi + 2);
    // b) 当前s[si]，能被p[pi + (pi+1)]搞定，才有后续
    // 比如 a 与 a* 或者 a 与 .*
    if (s[si] == p[pi] || p[pi == '.'])
    {
      ans |= f1(s, p, si + 1, pi);
    }
    return ans;
  }

  bool isMatch3(string s, string p)
  {
    int N = s.length();
    int M = p.length();
    vector<vector<int>> dp(N + 1, vector<int>(M + 1));
    return f2(s, p, 0, 0, dp);
  }

  // 记忆化搜索
  bool f2(string s, string p, int si, int pi, vector<vector<int>> &dp)
  {
    if (dp[si][pi] != 0)
    {
      return dp[si][pi] == 1;
    }
    bool ans = false;
    if (pi == p.length())
    {
      ans = si == s.length();
    }
    else if (si == s.length())
    {
      ans = pi + 1 < p.length() && p[pi + 1] == '*' && f2(s, p, si, pi + 2, dp);
    }
    else if (pi + 1 >= p.length() || p[pi + 1] != '*')
    {
      ans = (s[si] == p[pi] || p[pi] == '.') && f2(s, p, si + 1, pi + 1, dp);
    }
    else
    {
      ans = f2(s, p, si, pi + 2, dp);
      if (s[si] == p[pi] || p[pi] == '.')
      {
        ans |= f2(s, p, si + 1, pi, dp);
      }
    }
    dp[si][pi] = ans ? 1 : -1;
    return ans;
  }
};

void testIsMatch()
{
  Solution s;
  EXPECT_FALSE(s.isMatch1("aa", "a"));
  EXPECT_TRUE(s.isMatch1("aa", "a*"));
  EXPECT_TRUE(s.isMatch1("ab", ".*"));
  EXPECT_FALSE(s.isMatch2("aa", "a"));
  EXPECT_TRUE(s.isMatch2("aa", "a*"));
  EXPECT_TRUE(s.isMatch2("ab", ".*"));
  EXPECT_FALSE(s.isMatch3("aa", "a"));
  EXPECT_TRUE(s.isMatch3("aa", "a*"));
  EXPECT_TRUE(s.isMatch3("ab", ".*"));
  EXPECT_SUMMARY;
}

int main()
{
  testIsMatch();
  return 0;
}
