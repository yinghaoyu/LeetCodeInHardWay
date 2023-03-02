#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string printBin(double num)
  {
    string ans = "0.";
    for (int i = 0; i < 6; i++)
    {
      num *= 2;
      if (num >= 1)
      {
        ans.append("1");
        if (--num == 0)
        {
          return ans;
        }
      }
      else
      {
        ans.append("0");
      }
    }
    return "ERROR";
  }
};

void testPrintBin()
{
  Solution s;
  EXPECT_TRUE("0.101" == s.printBin(0.625));
  EXPECT_TRUE("ERROR" == s.printBin(0.1));
  EXPECT_SUMMARY;
}

int main()
{
  testPrintBin();
  return 0;
}
