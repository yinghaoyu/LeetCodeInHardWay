#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// seem as leetcode 0852
// https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/
// see at Problem_0852_peakIndexInMountainArray.cc
class Solution
{
 public:
  int peakIndexInMountainArray(vector<int> &arr)
  {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right)
    {
      int mid = (right - left) / 2 + left;
      if (mid > 0 && arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1])
      {
        return mid;
      }
      else if (arr[mid] < arr[mid + 1])
      {
        left = mid + 1;
      }
      else if (arr[mid - 1] > arr[mid])
      {
        right = mid - 1;
      }
    }
    return -1;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {0, 1, 0};
  vector<int> n2 = {0, 2, 1, 0};
  vector<int> n3 = {0, 10, 5, 2};
  vector<int> n4 = {3, 5, 3, 2, 0};
  EXPECT_EQ_INT(1, s.peakIndexInMountainArray(n1));
  EXPECT_EQ_INT(1, s.peakIndexInMountainArray(n2));
  EXPECT_EQ_INT(1, s.peakIndexInMountainArray(n3));
  EXPECT_EQ_INT(1, s.peakIndexInMountainArray(n4));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
