#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isAnagram(string s, string t)
  {
    if (s.length() != t.length())
    {
      return false;
    }
    vector<int> cnt(256);
    for (auto &c : s)
    {
      cnt[c]++;
    }
    for (auto &c : t)
    {
      if (--cnt[c] < 0)
      {
        return false;
      }
    }
    return true;
  }
};

void testIsAnagram()
{
  Solution s;
  EXPECT_TRUE(s.isAnagram("anagram", "nagaram"));
  EXPECT_FALSE(s.isAnagram("rat", "car"));
  EXPECT_SUMMARY;
}

int main()
{
  testIsAnagram();
  return 0;
}
