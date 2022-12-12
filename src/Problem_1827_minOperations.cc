#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minOperations(vector<int> &nums)
  {
    int n = nums.size();
    int pre = nums[0];
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
      pre = std::max(pre + 1, nums[i]);
      ans += pre - nums[i];
    }
    return ans;
  }
};

void testMinOperations()
{
  Solution s;
  vector<int> n1 = {1, 1, 1};
  vector<int> n2 = {1, 5, 2, 4, 1};
  vector<int> n3 = {8};
  EXPECT_EQ_INT(3, s.minOperations(n1));
  EXPECT_EQ_INT(14, s.minOperations(n2));
  EXPECT_EQ_INT(0, s.minOperations(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMinOperations();
  return 0;
}
