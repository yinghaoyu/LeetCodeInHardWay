#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string removeKdigits(string num, int k)
  {
    vector<char> stack;
    string ans;
    for (int i = 0; i < num.length(); i++)
    {
      // 单调递增栈
      while (!ans.empty() && ans.back() > num[i] && k > 0)
      {
        k--;
        ans.pop_back();
      }
      ans.push_back(num[i]);
    }
    while (k > 0)
    {
      k--;
      ans.pop_back();
    }
    // 没有字符了
    if (ans.empty())
    {
      return "0";
    }
    // 删除前导0
    while (ans.length() > 1 && ans[0] == '0')
    {
      ans.erase(0, 1);
    }
    return ans;
  }
};

void testRemoveKdigits()
{
  Solution s;
  EXPECT_TRUE("1219" == s.removeKdigits("1432219", 3));
  EXPECT_TRUE("200" == s.removeKdigits("10200", 1));
  EXPECT_TRUE("0" == s.removeKdigits("10", 2));
  EXPECT_SUMMARY;
}

int main()
{
  testRemoveKdigits();
  return 0;
}
