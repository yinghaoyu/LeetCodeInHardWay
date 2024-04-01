#include <iostream>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int firstMissingPositive(vector<int>& nums)
  {
    // 通过置换，把数组变成，第i-1个位置的元素为i
    // [3, 4, -1, 1]变成[1, -1, 3, 4]
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
      {
        std::swap(nums[nums[i] - 1], nums[i]);
      }
    }
    for (int i = 0; i < n; i++)
    {
      if (nums[i] != i + 1)
      {
        return i + 1;
      }
    }
    return n + 1;
  }
};

void testFirstMissingPositive()
{
  Solution s;
  vector<int> n1 = {1, 2, 0};
  vector<int> n2 = {3, 4, -1, 1};
  vector<int> n3 = {7, 8, 9, 11, 12};
  EXPECT_EQ_INT(3, s.firstMissingPositive(n1));
  EXPECT_EQ_INT(2, s.firstMissingPositive(n2));
  EXPECT_EQ_INT(1, s.firstMissingPositive(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testFirstMissingPositive();
  return 0;
}
