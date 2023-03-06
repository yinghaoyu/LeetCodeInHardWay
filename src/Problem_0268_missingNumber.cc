#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 此题和41题类似
  // 下标循环怼
  int missingNumber1(vector<int> &nums)
  {
    int l = 0;
    int r = nums.size();
    while (l < r)
    {
      if (nums[l] == l)
      {
        // 已经在原来位置
        l++;
      }
      else if (nums[l] < l || nums[l] >= r || nums[nums[l]] == nums[l])
      {
        // 把超出范围的值都往后移动
        swap(nums, l, --r);
      }
      else
      {
        // nums[l]应该在去跟nums[l]位置上的值交换
        // 例如nums[2] = 5应该去跟 5位置上的值交换，即nums[5]
        // 新换来的值可能没达到条件，需要继续判断，l保持不变
        swap(nums, l, nums[l]);
      }
    }
    return l;
  }

  void swap(vector<int> &nums, int i, int j)
  {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
  }

  // 利用异或性质
  int missingNumber2(vector<int> &nums)
  {
    int ans = 0;
    int n = nums.size();
    for (int i = 1; i <= n; i++)
    {
      ans ^= i;
    }
    for (int i = 0; i < n; i++)
    {
      ans ^= nums[i];
    }
    return ans;
  }
};

void testMissingNumber()
{
  Solution s;
  vector<int> n1 = {3, 0, 1};
  vector<int> n2 = {0, 1};
  vector<int> n3 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
  EXPECT_EQ_INT(2, s.missingNumber1(n1));
  EXPECT_EQ_INT(2, s.missingNumber1(n2));
  EXPECT_EQ_INT(8, s.missingNumber1(n3));
  EXPECT_EQ_INT(2, s.missingNumber2(n1));
  EXPECT_EQ_INT(2, s.missingNumber2(n2));
  EXPECT_EQ_INT(8, s.missingNumber2(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMissingNumber();
  return 0;
}
