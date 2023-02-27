#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findPeakElement(vector<int> &nums)
  {
    int n = nums.size();
    if (n < 2)
    {
      return 0;
    }
    if (nums[0] > nums[1])
    {
      return 0;
    }
    if (nums[n - 1] > nums[n - 2])
    {
      return n - 1;
    }
    int l = 1;
    int r = n - 2;
    int m = 0;
    // 为什么二分查找大的那一半一定会有峰值呢？
    // 很简单，上坡必有坡顶，就算一直递增到最后一个元素，也满足条件，因为nums[-1] = nums[n] = -∞
    while (l <= r)
    {
      m = (r - l) / 2 + l;
      if (nums[m - 1] < nums[m] && nums[m] > nums[m + 1])
      {
        return m;
      }
      else if (nums[m - 1] > nums[m])
      {
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return l;
  }
};

void testFindPeakElement()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 1};
  vector<int> n2 = {1, 2, 1, 3, 5, 6, 4};
  EXPECT_EQ_INT(2, s.findPeakElement(n1));
  EXPECT_EQ_INT(5, s.findPeakElement(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testFindPeakElement();
  return 0;
}
