#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isPalindrome(string &s, int L, int R)
  {
    for (int i = L, j = R; i < j; i++, j--)
    {
      if (s[i] != s[j])
      {
        return false;
      }
    }
    return true;
  }
  bool validPalindrome(string s)
  {
    int n = s.length();
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
      if (s[left] == s[right])
      {
        left++;
        right--;
      }
      else
      {
        return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
      }
    }
    return true;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE(s.validPalindrome("aba"));
  EXPECT_TRUE(s.validPalindrome("abca"));
  EXPECT_FALSE(s.validPalindrome("abc"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
