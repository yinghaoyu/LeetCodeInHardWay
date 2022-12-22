#include <iostream>
#include <string>

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
};

void testIsMatch()
{
  Solution s;
  EXPECT_FALSE(s.isMatch1("aa", "a"));
  EXPECT_TRUE(s.isMatch1("aa", "a*"));
  EXPECT_TRUE(s.isMatch1("ab", ".*"));
  EXPECT_SUMMARY;
}

int main()
{
  testIsMatch();
  return 0;
}
