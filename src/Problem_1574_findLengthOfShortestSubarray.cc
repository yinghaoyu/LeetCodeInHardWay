#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 参考链接：https://leetcode.cn/problems/shortest-subarray-to-be-removed-to-make-array-sorted/solution/dong-hua-yi-xie-jiu-cuo-liang-chong-xie-iijwz/
class Solution
{
 public:
  int findLengthOfShortestSubarray(vector<int> &arr)
  {
    // 找到要删除的子数组的区间(left, right)
    int n = arr.size();
    int right = n - 1;
    while (right > 0 && arr[right - 1] <= arr[right])
    {
      // right 的最小值为最长非递减后缀的起始位置
      right--;
    }
    if (right == 0)
    {
      // arr已经是非递减数组
      return 0;
    }
    //此时arr[right-1] > arr[right]
    int ans = right;  // 删除区间[0,right)
    // 枚举所有区间
    for (int left = 0; left == 0 || arr[left - 1] <= arr[left]; left++)
    {
      while (right < n && arr[right] < arr[left])
      {
        right++;
      }
      // 此时 arr[left] <= arr[right]，删除区间(left, right)
      ans = std::min(ans, right - left - 1);
    }
    return ans;
  }
};

void testFindLengthOfShortestSubarray()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 10, 4, 2, 3, 5};
  vector<int> n2 = {5, 4, 3, 2, 1};
  vector<int> n3 = {1, 2, 3};
  EXPECT_EQ_INT(3, s.findLengthOfShortestSubarray(n1));
  EXPECT_EQ_INT(4, s.findLengthOfShortestSubarray(n2));
  EXPECT_EQ_INT(0, s.findLengthOfShortestSubarray(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testFindLengthOfShortestSubarray();
  return 0;
}
