#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 降序是最大的排列
  // 升序是最小的排列
  //                7
  //              ↗
  //     9      6
  //   ↗  ↘   ↗
  // 1      4
  vector<int> prevPermOpt1(vector<int> &arr)
  {
    int n = arr.size();
    int firstLarge = -1;
    for (int i = n - 2; i >= 0; i--)
    {
      if (arr[i] > arr[i + 1])
      {
        // 找第一个降序，为9
        firstLarge = i;
        break;
      }
    }
    if (firstLarge == -1)
    {
      return arr;
    }
    int rightClosestLess = firstLarge + 1;
    for (int i = firstLarge + 1; i < n; i++)
    {
      // 再从9的右边
      // 从左往右找最大且小于9的，为7
      if (arr[i] > arr[rightClosestLess] && arr[i] < arr[firstLarge])
      {
        rightClosestLess = i;
      }
    }
    std::swap(arr[firstLarge], arr[rightClosestLess]);
    return arr;
  }
};

void testPrevPermOpt1()
{
  Solution s;
  vector<int> n1 = {3, 2, 1};
  vector<int> o1 = {3, 1, 2};
  vector<int> n2 = {1, 1, 5};
  vector<int> o2 = {1, 1, 5};
  vector<int> n3 = {1, 9, 4, 6, 7};
  vector<int> o3 = {1, 7, 4, 6, 9};
  vector<int> n4 = {3, 1, 1, 3};
  vector<int> o4 = {1, 3, 1, 3};
  EXPECT_TRUE(o1 == s.prevPermOpt1(n1));
  EXPECT_TRUE(o2 == s.prevPermOpt1(n2));
  EXPECT_TRUE(o3 == s.prevPermOpt1(n3));
  EXPECT_TRUE(o4 == s.prevPermOpt1(n4));
  EXPECT_SUMMARY;
}

int main()
{
  testPrevPermOpt1();
  return 0;
}
