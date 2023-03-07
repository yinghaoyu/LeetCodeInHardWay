#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void moveZeroes(vector<int> &nums)
  {
    int to = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      if (nums[i] != 0)
      {
        swap(nums, to++, i);
      }
    }
  }

  void swap(vector<int> &nums, int i, int j)
  {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
  }
};

void testMoveZeroes()
{
  Solution s;
  vector<int> n1 = {0, 1, 0, 3, 12};
  vector<int> o1 = {1, 3, 12, 0, 0};
  vector<int> n2 = {0};
  vector<int> o2 = {0};
  s.moveZeroes(n1);
  s.moveZeroes(n2);
  EXPECT_TRUE(o1 == n1);
  EXPECT_TRUE(o2 == n2);
  EXPECT_SUMMARY;
}

int main()
{
  testMoveZeroes();
  return 0;
}
