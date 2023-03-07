#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findDuplicate(vector<int> &nums)
  {
    if (nums.size() < 2)
    {
      return -1;
    }
    int slow = nums[0];
    int fast = nums[nums[0]];
    while (slow != fast)
    {
      slow = nums[slow];
      fast = nums[nums[fast]];
    }
    fast = 0;
    while (slow != fast)
    {
      fast = nums[fast];
      slow = nums[slow];
    }
    return slow;
  }
};

void testFindDuplicate()
{
  Solution s;
  vector<int> n1 = {1, 3, 4, 2, 2};
  vector<int> n2 = {3, 1, 3, 4, 2};
  EXPECT_EQ_INT(2, s.findDuplicate(n1));
  EXPECT_EQ_INT(3, s.findDuplicate(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testFindDuplicate();
  return 0;
}
