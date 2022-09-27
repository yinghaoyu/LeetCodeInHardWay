#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool CheckPermutation(string s1, string s2)
  {
    if (s1.length() != s2.length())
    {
      return false;
    }
    int cnt[256] = {0};
    int diff = 0;
    for (int i = 0; i < s1.length(); i++)
    {
      if (++cnt[s1[i]] == 1)
      {
        diff++;
      }
      if (--cnt[s2[i]] == 0)
      {
        diff--;
      }
    }
    return diff == 0;
  }
};

void testCheckPermutation()
{
  Solution s;
  EXPECT_TRUE(s.CheckPermutation("abc", "bca"));
  EXPECT_FALSE(s.CheckPermutation("abc", "bad"));
  EXPECT_SUMMARY;
}

int main()
{
  testCheckPermutation();
  return 0;
}
