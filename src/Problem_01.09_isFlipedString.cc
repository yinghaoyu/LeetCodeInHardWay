#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isFlipedString(string s1, string s2) { return s1.length() == s2.length() && (s1 + s1).find(s2) != string::npos; }
};

void testIsFlipedString()
{
  Solution s;
  EXPECT_TRUE(s.isFlipedString("waterbottle", "erbottlewat"));
  EXPECT_FALSE(s.isFlipedString("aa", "aba"));
  EXPECT_SUMMARY;
}

int main()
{
  testIsFlipedString();
  return 0;
}
