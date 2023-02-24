#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // https://leetcode.cn/problems/decrease-elements-to-make-array-zigzag/solution/mei-you-si-lu-yi-bu-bu-ti-shi-ni-si-kao-cm0h2/
  int movesToMakeZigzag(vector<int> &nums)
  {
    vector<int> ans(2);
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      int left = i > 0 ? nums[i - 1] : INT32_MAX;
      int right = i < n - 1 ? nums[i + 1] : INT32_MAX;
      int m = std::min(left, right) - 1;
      ans[i & 1] += std::max(nums[i] - m, 0);
    }
    return std::min(ans[0], ans[1]);
  }
};

void testMovesToMakeZigzag()
{
  Solution s;
  vector<int> n1 = {1, 2, 3};
  vector<int> n2 = {9, 6, 1, 6, 2};
  EXPECT_EQ_INT(2, s.movesToMakeZigzag(n1));
  EXPECT_EQ_INT(4, s.movesToMakeZigzag(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testMovesToMakeZigzag();
  return 0;
}
