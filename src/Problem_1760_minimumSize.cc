#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minimumSize(vector<int> &nums, int maxOperations)
  {
    int left = 1, right = *std::max_element(nums.begin(), nums.end());
    int ans = 0;
    // 给定 maxOperations 次操作次数，能否可以使得单个袋子里球数目的最大值不超过 mid
    // 当 mid 增加时，操作次数会减少，因此 mid 具有单调性
    while (left <= right)
    {
      int mid = left + (right - left) / 2;
      long long op = 0;
      for (int &x : nums)
      {
        // 把单个袋子x个球拆分成不超过mid个球，需要的操作数
        op += (x - 1) / mid;
      }
      if (op <= maxOperations)
      {
        ans = mid;
        right = mid - 1;
      }
      else
      {
        left = mid + 1;
      }
    }
    return ans;
  }
};

void testMininumSize()
{
  Solution s;
  vector<int> n1 = {9};
  vector<int> n2 = {2, 4, 8, 2};
  EXPECT_EQ_INT(3, s.minimumSize(n1, 2));
  EXPECT_EQ_INT(2, s.minimumSize(n2, 4));
  EXPECT_SUMMARY;
}

int main()
{
  testMininumSize();
  return 0;
}
