#include <bitset>
#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool queryString(string s, int n)
  {
    // 从 n 开始，能尽快让函数结束
    for (int i = n; i >= 1; i--)
    {
      auto x = bitset<32>(i).to_string();
      x = x.substr(x.find('1'));
      if (s.find(x) == string::npos)
      {
        return false;
      }
    }
    return true;
  }
};

void testQueryString()
{
  Solution s;
  EXPECT_TRUE(s.queryString("0110", 3));
  EXPECT_FALSE(s.queryString("0110", 4));
  EXPECT_SUMMARY;
}

int main()
{
  testQueryString();
  return 0;
}
