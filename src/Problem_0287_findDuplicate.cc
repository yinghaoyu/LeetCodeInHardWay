#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 解法一：排序法，修改了数组，不符合要求
  // 解法二：计数法，空间复杂度不是常数，不符合要求
  // 解法三：标记法，遍历一遍数组，把值改成负值，当遇到负数时，即为重复数。修改了数组，不符合要求。
  // 解法四：二分查找，所有数的个数为n，左右两边至少会有一边，数的个数 > 坑的个数。
  // 解法五：双指针，符合要求
  int findDuplicate1(vector<int> &nums)
  {
    int n = nums.size();
    int l = 1;
    int r = n - 1;
    int ans = -1;
    while (l <= r)
    {
      int mid = (r - l) / 2 + l;
      int cnt = 0;
      for (int i = 0; i < n; i++)
      {
        // [l, mid]
        // [mid + 1,r]
        // 计算左半区符合坑内的数据
        cnt += (l <= nums[i] && nums[i] <= mid);
      }
      if (cnt <= mid - l + 1)
      {
        // 左半区数的个数 <= 左半区坑的个数
        // 说明没有重复的数在这个区间
        l = mid + 1;
      }
      else
      {
        ans = mid;
        r = mid - 1;
      }
    }
    return ans;
  }

  int findDuplicate2(vector<int> &nums)
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
  EXPECT_EQ_INT(2, s.findDuplicate1(n1));
  EXPECT_EQ_INT(3, s.findDuplicate1(n2));
  EXPECT_EQ_INT(2, s.findDuplicate2(n1));
  EXPECT_EQ_INT(3, s.findDuplicate2(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testFindDuplicate();
  return 0;
}
