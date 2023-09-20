#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int singleNonDuplicate(vector<int> &nums)
  {
    // 假设下标 x 位置的数不同，可以发现，
    // 位于 x 位置左边的数，nums[y] = nums[y+1]，y一定是偶数
    // 位于 y 位置右边的数，nums[y] = nums[y+1]，y一定是奇数
    // 那么可以利用这一性质，
    // 当 y 为偶数时，可以判断 nums[y] == nums[y+1]，如果符合，说明当前在 x 的左侧
    // 当 y 为奇数时，可以判断 nums[y-1] == nums[y]，如果符合，说明当前在 x 的左侧
    // 已知，对于偶数 y + 1 = y ^ 1，对于奇数 y - 1 = y ^ 1，因此可直接计算 y ^ 1来得到下标
    int left = 0;
    int right = nums.size() - 1;
    while (left < right)
    {
      int mid = (right - left) / 2 + left;
      if (nums[mid] == nums[mid ^ 1])
      {
        left = mid + 1;
      }
      else
      {
        right = mid;
      }
    }
    return nums[left];
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, 1, 2, 3, 3, 4, 4, 8, 8};
  vector<int> n2 = {3, 3, 7, 7, 10, 11, 11};
  EXPECT_EQ_INT(2, s.singleNonDuplicate(n1));
  EXPECT_EQ_INT(10, s.singleNonDuplicate(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
