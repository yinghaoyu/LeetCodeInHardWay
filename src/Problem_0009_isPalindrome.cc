#include <pthread.h>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isPalindrome(int x)
  {
    if (x < 0)
    {
      return false;
    }
    int help = 1;
    while (x / help >= 10)
    {
      help *= 10;
    }
    while (x != 0)
    {
      if (x / help != x % 10)
      {
        return false;
      }
      x = (x % help) / 10;
      help /= 100;
    }
    return true;
  }
};

void testIsPalindrome()
{
  Solution s;
  EXPECT_TRUE(s.isPalindrome(121));
  EXPECT_FALSE(s.isPalindrome(-121));
  EXPECT_FALSE(s.isPalindrome(10));
  EXPECT_SUMMARY;
}

int main()
{
  testIsPalindrome();
  return 0;
}
