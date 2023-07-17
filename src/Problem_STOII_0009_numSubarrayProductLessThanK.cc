#include <iostream>
#include <vector>

using namespace std;

// 与 leetcode 0713 相同
// https://leetcode.cn/problems/subarray-product-less-than-k/
// see at Problem_0713_numSubarrayProductLessThanK.cc
class Solution
{
 public:
  int numSubarrayProductLessThanK(vector<int> &nums, int k)
  {
    int n = nums.size();
    int left = 0;
    int right = 0;
    int p = 1;
    int ans = 0;
    while (right < n)
    {
      p *= nums[right];
      while (left <= right && p >= k)
      {
        p /= nums[left];
        left++;
      }
      ans += right - left + 1;
      right++;
    }
    return ans;
  }
};
