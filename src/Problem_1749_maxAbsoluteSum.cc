#include <cstdio>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxAbsoluteSum(vector<int> &nums)
  {
    // 表示必须以nums[i]为结尾的子数组，最小值是多少
    int negativeSum = 0;
    // 表示必须以nums[i]为结尾的子数组，最大值是多少
    int positiveSum = 0;
    int negativeMin = INT32_MAX;
    int positiveMax = INT32_MIN;
    for (auto &num : nums)
    {
      negativeSum = negativeSum < 0 ? negativeSum + num : num;
      negativeMin = std::min(negativeMin, negativeSum);
      positiveSum = positiveSum > 0 ? positiveSum + num : num;
      positiveMax = std::max(positiveMax, positiveSum);
    }
    return std::max(positiveMax, -negativeMin);
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, -3, 2, 3, -4};
  vector<int> n2 = {2, -5, 1, -4, 3, -2};
  EXPECT_EQ_INT(5, s.maxAbsoluteSum(n1));
  EXPECT_EQ_INT(8, s.maxAbsoluteSum(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
