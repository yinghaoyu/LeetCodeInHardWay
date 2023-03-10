#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int firstUniqChar(string s)
  {
    int N = s.length();
    vector<int> cnt(26);
    for (char c : s)
    {
      cnt[c - 'a']++;
    }
    for (int i = 0; i < N; i++)
    {
      if (cnt[s[i] - 'a'] == 1)
      {
        return i;
      }
    }
    return -1;
  }
};

void testFirstUniqChar()
{
  Solution s;
  EXPECT_EQ_INT(0, s.firstUniqChar("leetcode"));
  EXPECT_EQ_INT(2, s.firstUniqChar("loveleetcode"));
  EXPECT_EQ_INT(-1, s.firstUniqChar("aabb"));
  EXPECT_SUMMARY;
}

int main()
{
  testFirstUniqChar();
  return 0;
}
