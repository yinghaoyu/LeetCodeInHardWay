#include <cstdint>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findUnsortedSubarray(vector<int>& nums)
  {
    if (nums.size() < 2)
    {
      return 0;
    }
    int N = nums.size();
    // max > 当前数，认为不达标
    // 从左往右遍历，记录最右不达标的位置
    int right = -1;
    int max = INT32_MIN;
    for (int i = 0; i < N; i++)
    {
      if (max > nums[i])
      {
        right = i;
      }
      max = std::max(max, nums[i]);
    }
    // min < 当前数，认为不达标
    // 从右往左遍历，记录最左不达标的位置
    int min = INT32_MAX;
    int left = N;
    for (int i = N - 1; i >= 0; i--)
    {
      if (min < nums[i])
      {
        left = i;
      }
      min = std::min(min, nums[i]);
    }
    return std::max(0, right - left + 1);
  }
};

void testFindUnsortedSubarray()
{
  Solution s;
  vector<int> n1 = {2, 6, 4, 8, 10, 9, 15};
  vector<int> n2 = {1, 2, 3, 4};
  vector<int> n3 = {1};
  EXPECT_EQ_INT(5, s.findUnsortedSubarray(n1));
  EXPECT_EQ_INT(0, s.findUnsortedSubarray(n2));
  EXPECT_EQ_INT(0, s.findUnsortedSubarray(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testFindUnsortedSubarray();
  return 0;
}
