#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countConsistentStrings(string allowed, vector<string> &words)
  {
    int mask = 0;
    int ans = 0;
    for (char &c : allowed)
    {
      mask |= 1 << (c - 'a');
    }
    for (string &w : words)
    {
      int seen = 0;
      for (char &c : w)
      {
        seen |= 1 << (c - 'a');
      }
      if ((mask | seen) == mask)
      {
        ans++;
      }
    }
    return ans;
  }
};

void testCountConsistentStrings()
{
  Solution s;
  vector<string> n1 = {"ad", "bd", "aaab", "baa", "badab"};
  vector<string> n2 = {"a", "b", "c", "ab", "ac", "bc", "abc"};
  vector<string> n3 = {"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"};
  EXPECT_EQ_INT(2, s.countConsistentStrings("ab", n1));
  EXPECT_EQ_INT(7, s.countConsistentStrings("abc", n2));
  EXPECT_EQ_INT(4, s.countConsistentStrings("cad", n3));
  EXPECT_SUMMARY;
}

int main()
{
  testCountConsistentStrings();
  return 0;
}
