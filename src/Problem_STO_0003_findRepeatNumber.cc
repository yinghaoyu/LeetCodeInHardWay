#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findRepeatNumber(vector<int> &nums)
  {
    for (int n : nums)
    {
      if (n < 0 || n >= nums.size())
      {
        return -1;
      }
    }
    for (int i = 0; i < nums.size(); i++)
    {
      while (nums[i] != i && nums[nums[i]] != nums[i])
      {
        // 不断把nums[i]放在正确的位置nums[nums[i]]上
        swap(nums[i], nums[nums[i]]);
      }
      if (nums[i] != i && nums[nums[i]] == nums[i])
      {
        // 如果nums[i]已经在正确的位置上了
        // 但是nums[i] != i，说明了nums[i]重复
        return nums[i];
      }
    }
    return -1;
  }
};

void testFindRepeatNumber()
{
  Solution s;
  vector<int> n1 = {2, 3, 1, 0, 2, 5, 3};
  EXPECT_EQ_INT(2, s.findRepeatNumber(n1));
  EXPECT_SUMMARY;
}

int main()
{
  testFindRepeatNumber();
  return 0;
}
