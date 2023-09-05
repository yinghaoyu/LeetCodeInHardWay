#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minNumber(vector<int> &nums1, vector<int> &nums2)
  {
    unordered_set<int> s(nums1.begin(), nums1.end());
    int x = INT32_MAX;
    for (int num : nums2)
    {
      if (s.count(num))
      {
        x = std::min(x, num);
      }
    }
    if (x != INT32_MAX)
    {
      return x;
    }
    int a = *min_element(nums1.begin(), nums1.end());
    int b = *min_element(nums2.begin(), nums2.end());
    return std::min(a * 10 + b, b * 10 + a);
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {4, 1, 3};
  vector<int> n2 = {5, 7};
  vector<int> n3 = {3, 5, 2, 6};
  vector<int> n4 = {3, 1, 7};
  EXPECT_EQ_INT(15, s.minNumber(n1, n2));
  EXPECT_EQ_INT(3, s.minNumber(n3, n4));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
