#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minSubArrayLen(int target, vector<int> &nums)
  {
    int n = nums.size();
    int left = 0;
    int right = 0;
    int ans = INT32_MAX;
    int sum = 0;
    while (right < n)
    {
      sum += nums[right];
      while (sum >= target)
      {
        ans = std::min(ans, right - left + 1);
        sum -= nums[left];
        left++;
      }
      right++;
    }
    return ans == INT32_MAX ? 0 : ans;
  }
};
