#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minOperations(string s)
  {
    int ans = 0;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      char c = s[i];
      if (c != ('0' + i % 2))
      {
        ans++;
      }
    }
    return std::min(ans, n - ans);
  }
};

void testMinOperations()
{
  Solution s;
  EXPECT_EQ_INT(1, s.minOperations("0100"));
  EXPECT_EQ_INT(0, s.minOperations("10"));
  EXPECT_EQ_INT(2, s.minOperations("1111"));
  EXPECT_SUMMARY;
}

int main()
{
  testMinOperations();
  return 0;
}
