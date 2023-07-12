#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int alternateDigitSum(int n)
  {
    vector<int> nums;
    while (n)
    {
      nums.push_back(n % 10);
      n /= 10;
    }
    int ans = 0;
    bool neg = false;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
      ans += neg ? -nums[i] : nums[i];
      neg = !neg;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(4, s.alternateDigitSum(521));
  EXPECT_EQ_INT(1, s.alternateDigitSum(111));
  EXPECT_EQ_INT(0, s.alternateDigitSum(886996));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
