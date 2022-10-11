#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool areAlmostEqual(string s1, string s2)
  {
    if (s1.length() != s2.length())
    {
      return false;
    }
    int N = s1.length();
    int diff = N;
    int a = -1, b = -1;
    for (int i = 0; i < N; i++)
    {
      if (s1[i] == s2[i])
      {
        diff--;
      }
      else
      {
        if (a == -1)
        {
          a = i;
        }
        else
        {
          b = i;
        }
      }
    }
    return (diff == 2 && s1[a] == s2[b] && s2[a] == s1[b]) || diff == 0;
  }
};

void testAreAlmostEqual()
{
  Solution s;

  EXPECT_TRUE(s.areAlmostEqual("bank", "kanb"));
  EXPECT_FALSE(s.areAlmostEqual("attack", "defend"));
  EXPECT_TRUE(s.areAlmostEqual("kelb", "kelb"));
  EXPECT_SUMMARY;
}

int main()
{
  testAreAlmostEqual();
  return 0;
}
