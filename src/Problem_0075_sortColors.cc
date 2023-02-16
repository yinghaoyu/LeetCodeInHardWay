#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void swap(vector<int> &nums, int i, int j)
  {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
  }

  void sortColors(vector<int> &nums)
  {
    int l = 0;
    int r = nums.size() - 1;
    int index = 0;
    while (index <= r)
    {
      if (nums[index] == 1)
      {
        index++;
      }
      else if (nums[index] == 0)
      {
        swap(nums, index++, l++);
      }
      else
      {
        // nums[index] == 2
        // 换过来的数还需要再次比较
        swap(nums, index, r--);
      }
    }
  }
};

void testSortColors()
{
  Solution s;
  vector<int> n1 = {2, 0, 2, 1, 1, 0};
  vector<int> o1 = {0, 0, 1, 1, 2, 2};
  vector<int> n2 = {2, 0, 1};
  vector<int> o2 = {0, 1, 2};
  s.sortColors(n1);
  s.sortColors(n2);
  EXPECT_TRUE(o1 == n1);
  EXPECT_TRUE(o2 == n2);
  EXPECT_SUMMARY;
}

int main()
{
  testSortColors();
  return 0;
}
