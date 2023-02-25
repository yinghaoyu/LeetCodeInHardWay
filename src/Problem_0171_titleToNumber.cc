#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int titleToNumber(string columnTitle)
  {
    int ans = 0;
    for (int i = 0; i < columnTitle.length(); i++)
    {
      int num = columnTitle[i] - 'A' + 1;
      ans = ans * 26 + num;
    }
    return ans;
  }
};

void testTitleToNumber()
{
  Solution s;
  EXPECT_EQ_INT(1, s.titleToNumber("A"));
  EXPECT_EQ_INT(28, s.titleToNumber("AB"));
  EXPECT_EQ_INT(701, s.titleToNumber("ZY"));
  EXPECT_SUMMARY;
}

int main()
{
  testTitleToNumber();
  return 0;
}
