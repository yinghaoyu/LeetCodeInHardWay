#include <cctype>
#include <string>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool areNumbersAscending(string s)
  {
    int n = s.length();
    int i = 0;
    int j = 0;
    int pre = -1;
    while (i < n && j < n)
    {
      while (i < n && !isdigit(s[i]))
      {
        i++;
      }
      j = i;
      while (j < n && isdigit(s[j]))
      {
        j++;
      }
      if(i == n)
      {
        break;
      }
      string str = s.substr(i, j - i);
      int cur = stoi(str);
      if (cur <= pre)
      {
        return false;
      }
      pre = cur;
      i = j;
    }
    return true;
  }
};

void testAreNumbersAscending()
{
  Solution s;
  EXPECT_TRUE(s.areNumbersAscending("1 box has 3 blue 4 red 6 green and 12 yellow marbles"));
  EXPECT_FALSE(s.areNumbersAscending("hello world 5 x 5"));
  EXPECT_FALSE(s.areNumbersAscending("sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"));
  EXPECT_SUMMARY;
}

int main()
{
  testAreNumbersAscending();
  return 0;
}
