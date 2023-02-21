#include <cctype>
#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool validChar(char c) { return std::isalpha(c) || std::isdigit(c); }

  bool isEuqal(char c1, char c2) { return (c1 == c2) || ((c1 ^ 32) == c2); }

  bool isPalindrome(string s)
  {
    if (s.length() == 0)
    {
      return true;
    }
    int l = 0;
    int r = s.length() - 1;
    while (l <= r)
    {
      if (validChar(s[l]) && validChar(s[r]))
      {
        if (!isEuqal(s[l], s[r]))
        {
          return false;
        }
        l++;
        r--;
      }
      else
      {
        l += validChar(s[l]) ? 0 : 1;
        r -= validChar(s[r]) ? 0 : 1;
      }
    }
    return true;
  }
};

void testIsPalindrome()
{
  Solution s;
  EXPECT_TRUE(s.isPalindrome("A man, a plan, a canal: Panama"));
  EXPECT_FALSE(s.isPalindrome("race a car"));
  EXPECT_TRUE(s.isPalindrome(" "));
  EXPECT_SUMMARY;
}

int main()
{
  testIsPalindrome();
  return 0;
}
