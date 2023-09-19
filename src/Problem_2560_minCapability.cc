#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minCapability(vector<int> &nums, int k)
  {
    int left = *min_element(nums.begin(), nums.end());
    int right = *max_element(nums.begin(), nums.end());
    while (left < right)
    {
      // 尝试最小的偷钱能力
      int mid = (right - left) / 2 + left;
      // visited 用于限制相邻的不能同时偷
      bool visited = false;
      int count = 0;
      for (int x : nums)
      {
        if (x <= mid && !visited)
        {
          // 计算当前的偷钱能力能覆盖多少个房间
          count++;
          visited = true;
        }
        else
        {
          visited = false;
        }
      }
      if (count >= k)
      {
        // 符合条件，右窗口不断左移，尽量取最小的偷钱能力
        right = mid;
      }
      else
      {
        left = mid + 1;
      }
    }
    return right;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {2, 3, 5, 9};
  vector<int> n2 = {2, 7, 9, 3, 1};
  EXPECT_EQ_INT(5, s.minCapability(n1, 2));
  EXPECT_EQ_INT(2, s.minCapability(n2, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
