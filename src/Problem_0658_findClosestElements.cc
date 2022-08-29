#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 这道题可以看作求一个大小为 k 的区间，使区间内元素与 x 的距离的最大值最小，
// 这个最大值显然只与区间两端点有关，
// 设区间左端点为 i 的话，就是要让max(x - arr[i], arr[i + k - 1] - x)最小。
// 然后注意到x - arr[i]递减，arr[i + k - 1] - x递增，
// 两者的交点就是最小值，用二分可以找到这个交点

class Solution
{
 public:
  vector<int> findClosestElements(vector<int> &arr, int k, int x)
  {
    // l ... r 是包含k个元素的区间
    int l = 0;
    int r = arr.size() - k;
    // 寻找长度为k的区间的左端点l
    // 这个区间是arr中，从左向右第一个满足 x - arr[l] <= arr[l + k - 1] - x 的区间
    // 因为arr的有序性才可以这么做
    while (l < r)
    {
      int m = l + ((r - l) >> 1);
      // 随着i增大，x - arr[i]递减，arr[i + k - 1] - x递增
      if (x - arr[m] > arr[m + k - 1] - x)
      {
        // 不符合条件就把区间右移1个单位
        l = m + 1;
      }
      else
      {
        r = m;
      }
    }
    // 因为在这个二分过程中，我们比较分析区间左端点和右端点的情况，
    // 一旦不满足 x - arr[lo] <= arr[lo + k - 1] - x，则右移即l = m + 1，
    // 但是此时我们并没有比较lo - 1和lo + k - 1处的情况，
    // 实际上这样二分下来得到的区间只能保证其中的 k - 1个数，
    // 而到底最后一个数字是在l - 1处还是在l + k - 1处就需要再判断一次
    if (l > 0 && std::abs(arr[l - 1] - x) <= std::abs(arr[l + k - 1] - x))
    {
      l--;
    }
    return vector<int>(arr.begin() + l, arr.begin() + l + k);
  }
};

bool isEqualVector(vector<int> arr1, vector<int> arr2)
{
  if (arr1.size() != arr2.size())
  {
    return false;
  }
  for (int i = 0; i < arr1.size(); i++)
  {
    if (arr1[i] != arr2[i])
    {
      return false;
    }
  }
  return true;
}

void testFindClosestElements()
{
  Solution s;
  vector<int> arr1 = {1, 2, 3, 4, 5};
  vector<int> out1 = {1, 2, 3, 4};
  int k1 = 4;
  int x1 = 3;

  vector<int> arr2 = {1, 2, 3, 4, 5};
  vector<int> out2 = {1, 2, 3, 4};
  int k2 = 4;
  int x2 = -1;
  EXPECT_TRUE(isEqualVector(s.findClosestElements(arr1, k1, x1), out1));
  EXPECT_TRUE(isEqualVector(s.findClosestElements(arr2, k2, x2), out2));
  EXPECT_SUMMARY;
}

int main()
{
  testFindClosestElements();
  return 0;
}
