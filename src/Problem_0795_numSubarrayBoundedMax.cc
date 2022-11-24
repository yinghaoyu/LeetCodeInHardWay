#include <math.h>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numSubarrayBoundedMax1(vector<int> &nums, int left, int right)
  {
    int ans = 0;
    int p1 = -1;
    int p2 = -1;
    int n = nums.size() - 1;
    for (int i = 0; i < n; i++)
    {
      // 将数组元素分三类
      // < left，用 0 表示；
      // >= left 且 <= right，用 1 表示；
      // > right，用 2 表示。
      // i 作为子数组右端点
      if (nums[i] >= left && nums[i] <= right)
      {
        p1 = i;
      }
      else if (nums[i] > right)
      {
        p2 = i;
        p1 = -1;
      }
      // 合法的左端点可以落在 (p2, p1] 之间
      if (p1 != -1)
      {
        ans += p1 - p2;
      }
    }
    return ans;
  }

  // 求出数组 nums 中所有元素 <= lower 的子数组数目
  int count(vector<int> &nums, int lower)
  {
    int res = 0, cur = 0;
    for (auto x : nums)
    {
      cur = x <= lower ? cur + 1 : 0;
      res += cur;
    }
    return res;
  }

  int numSubarrayBoundedMax2(vector<int> &nums, int left, int right) { return count(nums, right) - count(nums, left - 1); }
};

void testNumSubarrayBoundedMax()
{
  Solution s;
  vector<int> n1 = {2, 1, 4, 3};
  vector<int> n2 = {2, 9, 2, 5, 6};
  EXPECT_EQ_INT(3, s.numSubarrayBoundedMax1(n1, 2, 3));
  EXPECT_EQ_INT(7, s.numSubarrayBoundedMax1(n2, 2, 8));
  EXPECT_EQ_INT(3, s.numSubarrayBoundedMax2(n1, 2, 3));
  EXPECT_EQ_INT(7, s.numSubarrayBoundedMax2(n2, 2, 8));
  EXPECT_SUMMARY;
}

int main()
{
  testNumSubarrayBoundedMax();
  return 0;
}
