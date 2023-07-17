#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool checkInclusion(string s1, string s2)
  {
    int n = s1.length();
    int m = s2.length();
    vector<int> cnt(26);
    for (auto &c : s1)
    {
      cnt[c - 'a']--;
    }
    int left = 0;
    int right = 0;
    while (right < m)
    {
      int x = s2[right] - 'a';
      cnt[x]++;
      while (cnt[x] > 0)
      {
        cnt[s2[left] - 'a']--;
        left++;
      }
      if (right - left + 1 == n)
      {
        return true;
      }
      right++;
    }
    return false;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE(s.checkInclusion("ab", "eidbaooo"));
  EXPECT_FALSE(s.checkInclusion("ab", "eidboaoo"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
