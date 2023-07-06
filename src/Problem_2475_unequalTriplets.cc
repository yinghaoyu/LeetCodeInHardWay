#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int unequalTriplets(vector<int> &nums)
  {
    std::sort(nums.begin(), nums.end());
    int ans = 0;
    int n = nums.size();
    for (int i = 0, j = 0; i < n; i = j)
    {
      while (j < n && nums[j] == nums[i])
      {
        j++;
      }
      // "贡献法"
      // 左边元素的数目 i
      // 中间元素的数目 j - i
      // 右边元素的数目 n - j
      ans += i * (j - i) * (n - j);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {4, 4, 2, 4, 3};
  vector<int> n2 = {1, 1, 1, 1};
  EXPECT_EQ_INT(3, s.unequalTriplets(n1));
  EXPECT_EQ_INT(0, s.unequalTriplets(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
