#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string minWindow(string s, string t)
  {
    if (s.length() < t.length())
    {
      return "";
    }
    vector<int> map(256);
    for (char cha : t)
    {
      // 存target字符的个数
      map[cha]++;
    }
    int all = t.length();
    int L = 0;
    int R = 0;
    // -1(从来没找到过合法的)
    int minLen = -1;
    int ansl = -1;
    int ansr = -1;
    // [L..R)   [0,0)  R
    while (R != s.length())
    {
      map[s[R]]--;
      if (map[s[R]] >= 0)
      {
        // 说明窗口往右移动，s[R]是target的有效字符
        all--;
      }
      if (all == 0)
      {
        // 在R往右移的过程中，all == 0 说明此时 [L, R] 内刚好包含了target
        while (map[s[L]] < 0)
        {
          // 尝试缩小左边界L，忽视非target内的字符
          map[s[L++]]++;
        }
        if (minLen == -1 || minLen > R - L + 1)
        {
          // 记录结果
          minLen = R - L + 1;
          ansl = L;
          ansr = R;
        }
        // 计算下一个位置
        all++;
        map[s[L++]]++;
      }
      R++;
    }
    return minLen == -1 ? "" : s.substr(ansl, ansr + 1 - ansl);
  }
};

void testMinWindow()
{
  Solution s;
  EXPECT_TRUE("BANC" == s.minWindow("ADOBECODEBANC", "ABC"));
  EXPECT_TRUE("a" == s.minWindow("a", "a"));
  EXPECT_TRUE("" == s.minWindow("a", "aa"));
  EXPECT_SUMMARY;
}

int main()
{
  testMinWindow();
  return 0;
}
