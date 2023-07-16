#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string addBinary(string a, string b)
  {
    int n = a.length();
    int m = b.length();
    int i = n - 1;
    int j = m - 1;
    int carry = 0;
    string ans;
    while (i >= 0 || j >= 0 || carry > 0)
    {
      carry += i >= 0 ? a[i--] - '0' : 0;
      carry += j >= 0 ? b[j--] - '0' : 0;
      ans += std::to_string(carry % 2);
      carry /= 2;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE("100" == s.addBinary("11", "1"));
  EXPECT_TRUE("10101" == s.addBinary("1010", "1011"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
