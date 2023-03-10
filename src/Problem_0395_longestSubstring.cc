#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int longestSubstring(string s, int k)
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
};

void testLongestSubstring()
{
  Solution s;
  EXPECT_EQ_INT(3, s.longestSubstring("aaabb", 3));
  EXPECT_EQ_INT(5, s.longestSubstring("ababbc", 2));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestSubstring();
  return 0;
}
