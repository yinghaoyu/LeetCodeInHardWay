#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int secondHighest(string s)
  {
    int first = -1;
    int second = -1;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      if (std::isdigit(s[i]))
      {
        int number = s[i] - '0';
        if (number > first)
        {
          second = first;
          first = number;
        }
        else if (number < first && number > second)
        {
          second = number;
        }
      }
    }
    return second;
  }
};

void testSecondHighest()
{
  Solution s;
  EXPECT_EQ_INT(2, s.secondHighest("dfa12321afd"));
  EXPECT_EQ_INT(-1, s.secondHighest("abc1111"));
  EXPECT_SUMMARY;
}

int main()
{
  testSecondHighest();
  return 0;
}
