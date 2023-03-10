#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 暴力枚举
  int longestSubstring1(string s, int k)
  {
    int N = s.length();
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
      vector<int> cnt(256);
      int collect = 0;
      int satisfy = 0;
      for (int j = i; j < N; j++)
      {
        if (cnt[s[j]] == 0)
        {
          // 多少个不同的字符
          collect++;
        }
        if (cnt[s[j]] == k - 1)
        {
          // 多少个字符数满足 >= k 的字符
          satisfy++;
        }
        cnt[s[j]]++;
        if (collect == satisfy)
        {
          ans = std::max(ans, j - i + 1);
        }
      }
    }
    return ans;
  }

  int longestSubstring2(string s, int k)
  {
    int N = s.length();
    int max = 0;
    for (int require = 1; require <= 26; require++)
    {
      // a ~ z 出现的次数
      // cnt[0 1 2] a b c
      vector<int> cnt(26);
      // 窗口收集了集中字符
      int collect = 0;
      // 窗口出现次数 >=k 次的字符
      int satisfy = 0;
      int R = -1;
      for (int L = 0; L < N; L++)
      {
        //[L ... R]  R+1
        // 循环退出条件：新字符会打破 collext == require 平衡条件
        // 表示收集的字符已达到上限
        while (R + 1 < N && !(collect == require && cnt[s[R + 1] - 'a'] == 0))
        {
          R++;
          if (cnt[s[R] - 'a'] == 0)
          {
            collect++;
          }
          if (cnt[s[R] - 'a'] == k - 1)
          {
            satisfy++;
          }
          cnt[s[R] - 'a']++;
        }
        // [L ... R]
        if (satisfy == require)
        {
          max = std::max(max, R - L + 1);
        }
        // 为 L++ 做准备
        if (cnt[s[L] - 'a'] == 1)
        {
          collect--;
        }
        if (cnt[s[L] - 'a'] == k)
        {
          satisfy--;
        }
        cnt[s[L] - 'a']--;
      }
    }
    return max;
  }
};

void testLongestSubstring()
{
  Solution s;
  EXPECT_EQ_INT(3, s.longestSubstring1("aaabb", 3));
  EXPECT_EQ_INT(3, s.longestSubstring1("aaabb", 3));
  EXPECT_EQ_INT(5, s.longestSubstring2("ababbc", 2));
  EXPECT_EQ_INT(5, s.longestSubstring2("ababbc", 2));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestSubstring();
  return 0;
}
