#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/koko-eating-bananas/
// @sa Problem_0875_minEatingSpeed.cc

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
