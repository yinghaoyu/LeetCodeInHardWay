#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findFirst(vector<int> &nums, int target)
  {
    int l = 0;
    int r = nums.size() - 1;
    int index = -1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (target <= nums[m])
      {
        if(target == nums[m])
        {
          index = m;
        }
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return index;
  }

  int findLast(vector<int> &nums, int target)
  {
    int l = 0;
    int r = nums.size() - 1;
    int index = -1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (nums[m] <= target)
      {
        if(nums[m] == target)
        {
          index = m;
        }
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return index;
  }

  vector<int> searchRange(vector<int> &nums, int target)
  {
    int a = findFirst(nums, target);
    int b = findLast(nums, target);
    return {a, b};
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  return a == b;
}
void testSearchRange()
{
  Solution s;
  vector<int> n1 = {5, 7, 7, 8, 8, 10};
  vector<int> n2 = {};
  EXPECT_TRUE(isVectorEqual({3, 4}, s.searchRange(n1, 8)));
  EXPECT_TRUE(isVectorEqual({-1, -1}, s.searchRange(n1, 6)));
  EXPECT_TRUE(isVectorEqual({-1, -1}, s.searchRange(n2, 0)));
  EXPECT_SUMMARY;
}

int main()
{
  testSearchRange();
  return 0;
}
