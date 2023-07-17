#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int pivotIndex(vector<int> &nums)
  {
    int n = nums.size();
    int all = 0;
    for (int i = 0; i < n; i++)
    {
      all += nums[i];
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
      if (2 * sum + nums[i] == all)
      {
        return i;
      }
      sum += nums[i];
    }
    return -1;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, 7, 3, 6, 5, 6};
  vector<int> n2 = {1, 2, 3};
  vector<int> n3 = {2, 1, -1};
  EXPECT_EQ_INT(3, s.pivotIndex(n1));
  EXPECT_EQ_INT(-1, s.pivotIndex(n2));
  EXPECT_EQ_INT(0, s.pivotIndex(n3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
