#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int getIndexOf(string s, string m)
  {
    if (s.length() < m.length())
    {
      return -1;
    }
    if (m.length() == 0)
    {
      return 0;
    }
    int x = 0;
    int y = 0;
    vector<int> next = getNextArray(m);
    while (x < s.length() && y < m.length())
    {
      if (s[x] == m[y])
      {
        x++;
        y++;
      }
      else if (next[y] == -1)
      {
        x++;
      }
      else
      {
        y = next[y];
      }
    }
    return y == m.length() ? x - y : -1;
  }

  vector<int> getNextArray(string ms)
  {
    if (ms.length() == 1)
    {
      return {-1};
    }
    vector<int> next(ms.length());
    next[0] = -1;
    next[1] = 0;
    int i = 2;
    // cn代表，cn位置的字符，是当前和i-1位置比较的字符
    int cn = 0;
    while (i < next.size())
    {
      if (ms[i - 1] == ms[cn])
      {
        next[i++] = ++cn;
      }
      else if (cn > 0)
      {
        cn = next[cn];
      }
      else
      {
        next[i++] = 0;
      }
    }
    return next;
  }

  // KMP
  int strStr(string haystack, string needle) { return getIndexOf(haystack, needle); }
};

void testStrStr()
{
  Solution s;
  EXPECT_EQ_INT(0, s.strStr("sadbutsad", "sad"));
  EXPECT_EQ_INT(-1, s.strStr("leetcode", "leeto"));
  EXPECT_SUMMARY;
}

int main()
{
  testStrStr();
  return 0;
}
