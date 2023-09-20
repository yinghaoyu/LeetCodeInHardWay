#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minEatingSpeed(vector<int> &piles, int h)
  {
    int low = 1;
    int high = *max_element(piles.begin(), piles.end());
    while (low < high)
    {
      int mid = (high - low) / 2 + low;
      int count = 0;
      for (auto &x : piles)
      {
        count += (x + mid - 1) / mid;
      }
      if (count <= h)
      {
        high = mid;
      }
      else
      {
        low = mid + 1;
      }
    }
    return high;
  }
};

void test()
{
  Solution s;
  vector<int> p1 = {3, 6, 7, 11};
  vector<int> p2 = {30, 11, 23, 4, 20};
  vector<int> p3 = {30, 11, 23, 4, 20};
  EXPECT_EQ_INT(4, s.minEatingSpeed(p1, 8));
  EXPECT_EQ_INT(30, s.minEatingSpeed(p2, 5));
  EXPECT_EQ_INT(23, s.minEatingSpeed(p3, 6));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
