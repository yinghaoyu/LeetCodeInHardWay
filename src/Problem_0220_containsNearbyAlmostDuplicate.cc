#include <iostream>
#include <set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 二分查找
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int indexDiff, int valueDiff)
  {
    set<int> s;
    int n = nums.size();
    // nums 无序，依次遍历查找
    for (int i = 0; i < n; i++)
    {
      // 在前面 indexDiff 个数中，找到第一个 >= nums[i] - valueDiff 的数
      auto ptr = s.lower_bound(std::max(nums[i], INT32_MIN + valueDiff) - valueDiff);
      if (ptr != s.end() && *ptr <= std::min(nums[i], INT32_MAX - valueDiff) + valueDiff)
      {
        // 存在这个数，同时 <= nums[i] + valueDiff，满足条件
        return true;
      }
      s.insert(nums[i]);
      if (i >= indexDiff)
      {
        // 限制区间大小 indexDiff，删除最早的元素
        s.erase(nums[i - indexDiff]);
      }
    }
    return false;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 1};
  vector<int> n2 = {1, 5, 9, 1, 5, 9};
  EXPECT_TRUE(s.containsNearbyAlmostDuplicate(n1, 3, 0));
  EXPECT_FALSE(s.containsNearbyAlmostDuplicate(n2, 2, 3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
