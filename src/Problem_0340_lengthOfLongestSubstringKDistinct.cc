#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int lengthOfLongestSubstringKDistinct(string s, int k)
  {
    if (s.length() == 0 || k < 1)
    {
      return 0;
    }
    int N = s.length();
    vector<int> cnt(256);
    int diff = 0;
    int R = 0;
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
      // R 窗口的右边界
      while (R < N && (diff < k || (diff == k && cnt[s[R]] > 0)))
      {
        diff += cnt[s[R]] == 0 ? 1 : 0;
        cnt[s[R++]]++;
      }
      // R 来到违规的第一个位置
      ans = std::max(ans, R - i);
      diff -= cnt[s[i]] == 1 ? 1 : 0;
      cnt[s[i]]--;
    }
    return ans;
  }
};

void testLengthOfLongestSubstringKDistinct()
{
  Solution s;
  EXPECT_EQ_INT(3, s.lengthOfLongestSubstringKDistinct("eceba", 2));
  EXPECT_EQ_INT(2, s.lengthOfLongestSubstringKDistinct("aa", 1));
  EXPECT_SUMMARY;
}

int main()
{
  testLengthOfLongestSubstringKDistinct();
  return 0;
}
