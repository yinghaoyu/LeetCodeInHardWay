#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

// @sa https://www.bilibili.com/video/BV19Q4y1c7ko/
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
        // 字符匹配成功
        x++;
        y++;
      }
      else if (next[y] == -1)
      {
        // 进这个case的隐含条件，y==0
        x++;
      }
      else
      {
        // 利用next数组快速跳跃
        y = next[y];
      }
    }
    // 匹配成功 y == m长度
    return y == m.length() ? x - y : -1;
  }

  // next[i] 数组的含义为str[0...i-1]子串前后缀最大相同的长度（不包括整个字符串）
  // 比如 aabaabc
  //            ↑
  //            i=6
  //            此时next[6]=3，因为前缀串(aab)和后缀串(aab)相等的最大长度为3
  // 并且 next[0]=-1，坐标0前没字符，没有意义，定义为-1
  //      next[1]=0，当只有一个字符时，由于我们排除整个字符串，因此定义为0

  // 特殊例子 aaaaa
  //              ↑
  //              i=4
  //              此时next[4]=3，因为前缀串(aaa)和后缀串(aaa)相等的最大长度为3，
  //              而不是aaaa，因为我们排除整个字符串
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
