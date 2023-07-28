#include <iostream>
#include <set>
#include <vector>

#include "UnitTest.h"

using namespace std;

// seem as leetcode 0220
// https://leetcode-cn.com/problems/contains-duplicate-iii/
// see at Problem_0220_containsNearbyAlmostDuplicate.cc
class Solution
{
 public:
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
  {
    set<int> s;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      auto ptr = s.lower_bound(std::max(nums[i], INT32_MIN + t) - t);
      if (ptr != s.end() && *ptr <= std::min(nums[i], INT32_MAX - t) + t)
      {
        return true;
      }
      s.insert(nums[i]);
      if (i >= k)
      {
        s.erase(nums[i - k]);
      }
    }
    return false;
  }
};
