#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 旋转数组
class Solution
{
 public:
  int search(vector<int>& nums, int target)
  {
    // 将数组一分为二，其中一定有一个是有序的，另一个可能是有序，也能是部分有序。
    // 此时有序部分用二分法查找。
    // 无序部分再一分为二，其中一个一定有序，另一个可能有序，可能无序。就这样循环。
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
    // 为什么这里要取 <=，而不是 = ?
    // 因为是闭区间 [l, r]，当 l == r，需要处理只剩一个数的时候
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (nums[m] == target)
      {
        return m;
      }
      // 为什么这里要取 <=，而不是 = ？
      // 因为 (l + r) / 2 是向下取整，如果不加等号，m在区间只有两个数的时候一定是0
      // 那么 nums[0] < nums[m] 不成立，在else的条件下，右指针会向左偏移一位，
      // 从而失去第二个数，导致无法被查询。
      // 比如数组 [2, 1]，target = 1，可以查到2，但是查不到1

      // 这里为什么可以把nums[l]改成nums[0]？
      // 因为 [0, m)如果有序，那么 [l,m)也必然有序
      if (nums[l] <= nums[m])  // if (nums[0] <= nums[m])
      {
        // 左半区有序

        // 仔细想一下这里为什么取 <= 和 < ?
        // 因为是想在区间 [0, m) 内找 target

        // 这里为什么可以把nums[l]改成nums[0]？
        // 因为 [0, m)如果有序，那么 [l,m)也必然有序
        if (nums[l] <= target && target < nums[m])  // if (nums[0] <= target && target < nums[m])
        {
          // 因为 target < nums[m]，所以nums[m] 不是答案
          // 因此取 r = m - 1
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
        // 同理，这里是想在区间 (m, n-1] 内找 target

        // 这里为什么可以把nums[r]改成nums[n-1]？
        // 因为 (m, n-1]如果有序，那么 (m, r]也必然有序
        if (nums[m] < target && target <= nums[r])  // if (nums[m] < target && target <= nums[n-1])
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
