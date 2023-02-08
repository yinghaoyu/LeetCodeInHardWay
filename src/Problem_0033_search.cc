#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int search(vector<int> &nums, int target)
  {
    //将数组一分为二，其中一定有一个是有序的，另一个可能是有序，也能是部分有序。
    //此时有序部分用二分法查找。
    //无序部分再一分为二，其中一个一定有序，另一个可能有序，可能无序。就这样循环。
    int n = nums.size();
    if (n == 0)
    {
      return -1;
    }
    if (n == 1)
    {
      return nums[0] == target ? 0 : -1;
    }
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (nums[m] == target)
      {
        return m;
      }
      if (nums[0] <= nums[m])
      {
        // 左半区有序
        if (nums[0] <= target && target < nums[m])
        {
          r = m - 1;
        }
        else
        {
          l = m + 1;
        }
      }
      else
      {
        // 右半区有序
        if (nums[m] < target && target <= nums[n - 1])
        {
          l = m + 1;
        }
        else
        {
          r = m - 1;
        }
      }
    }
    return -1;
  }
};

void testSearch()
{
  Solution s;
  vector<int> n1 = {4, 5, 6, 7, 0, 1, 2};
  vector<int> n2 = {4, 5, 6, 7, 0, 1, 2};
  vector<int> n3 = {1};
  vector<int> n4 = {1, 3};
  EXPECT_EQ_INT(4, s.search(n1, 0));
  EXPECT_EQ_INT(-1, s.search(n2, 3));
  EXPECT_EQ_INT(-1, s.search(n3, 0));
  EXPECT_EQ_INT(-1, s.search(n4, 0));
  EXPECT_SUMMARY;
}

int main()
{
  testSearch();
  return 0;
}
