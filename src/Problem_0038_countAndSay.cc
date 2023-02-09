#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string process(int n)
  {
    if(n < 0)
    {
      return "";
    }
    if (n == 1)
    {
      return "1";
    }
    string pre = process(n - 1);
    string cur = "";
    char c = pre[0];
    int count = 1;
    for (int i = 1; i < pre.length(); i++)
    {
      if (pre[i] != c)
      {
        cur += std::to_string(count) + c;
        c = pre[i];
        count = 1;
      }
      else
      {
        count++;
      }
    }
    cur += std::to_string(count) + c;
    return cur;
  }

  string countAndSay(int n) { return process(n); }
};

void testCountAndSay()
{
  Solution s;
  EXPECT_TRUE("1" == s.countAndSay(1));
  EXPECT_TRUE("1211" == s.countAndSay(4));
  EXPECT_TRUE("111221" == s.countAndSay(5));
  EXPECT_SUMMARY;
}

int main()
{
  testCountAndSay();
  return 0;
}
