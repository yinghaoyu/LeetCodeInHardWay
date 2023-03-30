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
        swap(nums[i], nums[nums[i]]);
      }
      if (nums[i] != i && nums[nums[i]] == nums[i])
      {
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
