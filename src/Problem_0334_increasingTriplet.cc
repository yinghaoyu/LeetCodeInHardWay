#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool increasingTriplet(vector<int> &nums)
  {
    if (nums.size() < 3)
    {
      return false;
    }
    vector<int> ends(3);
    ends[0] = nums[0];
    int right = 0;
    int l = 0;
    int r = 0;
    int m = 0;
    for (int i = 1; i < nums.size(); i++)
    {
      l = 0;
      r = right;
      while (l <= r)
      {
        m = (r - l) / 2 + l;
        if (nums[i] > ends[m])
        {
          l = m + 1;
        }
        else
        {
          r = m - 1;
        }
      }
      right = std::max(right, l);
      if (right > 1)
      {
        return true;
      }
      ends[l] = nums[i];
    }
    return false;
  }
};

void testIncreasingTriplet()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 4, 5};
  vector<int> n2 = {5, 4, 3, 2, 1};
  vector<int> n3 = {2, 1, 5, 0, 4, 6};
  vector<int> n4 = {20, 100, 10, 12, 5, 13};
  EXPECT_TRUE(s.increasingTriplet(n1));
  EXPECT_FALSE(s.increasingTriplet(n2));
  EXPECT_TRUE(s.increasingTriplet(n3));
  EXPECT_TRUE(s.increasingTriplet(n4));
  EXPECT_SUMMARY;
}

int main()
{
  testIncreasingTriplet();
  return 0;
}
