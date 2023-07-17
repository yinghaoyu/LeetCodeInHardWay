#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string addStrings(string num1, string num2)
  {
    int n = num1.length();
    int m = num2.length();
    int i = n - 1;
    int j = m - 1;
    int carry = 0;
    string ans;
    while (i >= 0 || j >= 0 || carry > 0)
    {
      int x = i >= 0 ? num1[i--] - '0' : 0;
      int y = j >= 0 ? num2[j--] - '0' : 0;
      int sum = (x + y + carry);
      ans.push_back('0' + sum % 10);
      carry = sum / 10;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE("134" == s.addStrings("11", "123"));
  EXPECT_TRUE("533" == s.addStrings("456", "77"));
  EXPECT_TRUE("0" == s.addStrings("0", "0"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
