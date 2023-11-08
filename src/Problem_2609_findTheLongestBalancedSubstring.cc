#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findTheLongestBalancedSubstring(string s)
  {
    int zero = 0;
    int one = 0;
    int ans = 0;
    for (auto& c : s)
    {
      if (c == '0')
      {
        if (one > 0)
        {
          // 保证 0 前面的 1 全部失效
          zero = 0;
          one = 0;
        }
        zero++;
      }
      else
      {
        one++;
        ans = std::max(ans, 2 * std::min(zero, one));
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(6, s.findTheLongestBalancedSubstring("01000111"));
  EXPECT_EQ_INT(4, s.findTheLongestBalancedSubstring("00111"));
  EXPECT_EQ_INT(0, s.findTheLongestBalancedSubstring("111"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
