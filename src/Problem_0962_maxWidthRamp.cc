#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxWidthRamp(vector<int> &nums)
  {
    vector<int> stack;
    int N = nums.size();
    int max = 0;
    stack.push_back(0);
    for (int i = 1; i < N; i++)
    {
      // 利用单调递减栈减枝
      // *表示在栈中，当前遍历的为i，-表示后续需要遍历的元素
      // 9 8 1 0 1 9 4 0 4 1
      // * * * * ↑ - - - - -
      //         i         k
      // nums[i-1] = 0在栈中，为什么nums[i] = 1不需要入栈？
      // 假设后续存在元素k，满足 nums[i] <= nums[k]，那么nums[i-1] <= nums[k]也满足，且区间更长
      if (nums[stack.back()] > nums[i])
      {
        stack.push_back(i);
      }
    }
    for (int i = N - 1; i >= 0; i--)
    {
      // 具有单调性，因此可以使用滑动窗口统计结果
      while (!stack.empty() && nums[stack.back()] <= nums[i])
      {
        max = std::max(max, i - stack.back());
        stack.pop_back();
      }
    }
    return max;
  }
};

void testMaxWidthRamp()
{
  Solution s;
  vector<int> n1 = {6, 0, 8, 2, 1, 5};
  vector<int> n2 = {9, 8, 1, 0, 1, 9, 4, 0, 4, 1};
  EXPECT_EQ_INT(4, s.maxWidthRamp(n1));
  EXPECT_EQ_INT(7, s.maxWidthRamp(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxWidthRamp();
  return 0;
}
