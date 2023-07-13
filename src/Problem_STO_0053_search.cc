#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int nearLeft(vector<int> &arr, int target)
  {
    int left = 0;
    int right = arr.size() - 1;
    int index = -1;
    while (left <= right)
    {
      int mid = (right - left) / 2 + left;
      if (target <= arr[mid])
      {
        index = mid;
        right = mid - 1;
      }
      else
      {
        left = mid + 1;
      }
    }
    return index;
  }

  int nearRight(vector<int> &arr, int target)
  {
    int left = 0;
    int right = arr.size() - 1;
    int index = -1;
    if (arr[right] < target)
    {
      return -1;
    }
    while (left <= right)
    {
      int mid = (right - left) / 2 + left;
      if (arr[mid] <= target)
      {
        index = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return index;
  }

  int search(vector<int> &nums, int target)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    int left = nearLeft(nums, target);
    int right = nearRight(nums, target);

    return left != -1 && right != -1 ? right - left + 1 : 0;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {5, 7, 7, 8, 8, 10};
  EXPECT_EQ_INT(1, s.search(n1, 5));
  EXPECT_EQ_INT(2, s.search(n1, 8));
  EXPECT_EQ_INT(0, s.search(n1, 11));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
