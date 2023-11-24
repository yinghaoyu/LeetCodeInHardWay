#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countPairs(vector<int>& nums, int target)
  {
    std::sort(nums.begin(), nums.end());
    int ans = 0;
    for (int i = 0, j = nums.size() - 1; i < j; i++)
    {
      while (i < j && nums[i] + nums[j] >= target)
      {
        j--;
      }
      ans += j - i;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {-1, 1, 2, 3, 1};
  vector<int> n2 = {-6, 2, 5, -2, -7, -1, 3};
  EXPECT_EQ_INT(3, s.countPairs(n1, 2));
  EXPECT_EQ_INT(10, s.countPairs(n2, -2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
