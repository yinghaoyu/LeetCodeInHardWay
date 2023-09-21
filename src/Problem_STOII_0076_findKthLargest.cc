#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
// @sa Problem_0215_findKthLargest.cc

class Solution
{
 public:
  vector<int> partation(vector<int> &nums, int L, int R, int povit)
  {
    int less = L - 1;
    int more = R + 1;
    int cur = L;
    while (cur < more)
    {
      if (nums[cur] < povit)
      {
        swap(nums[++less], nums[cur++]);
      }
      else if (povit < nums[cur])
      {
        swap(nums[cur], nums[--more]);
      }
      else
      {
        cur++;
      }
    }
    return {less + 1, more - 1};
  }

  int process(vector<int> &nums, int L, int R, int index)
  {
    if (L == R)
    {
      return nums[L];
    }
    int povit = nums[L + random() % (R - L + 1)];
    vector<int> range = partation(nums, L, R, povit);
    if (index < range[0])
    {
      return process(nums, L, range[0] - 1, index);
    }
    else if (range[1] < index)
    {
      return process(nums, range[1] + 1, R, index);
    }
    else
    {
      return nums[index];
    }
  }
  int findKthLargest(vector<int> &nums, int k) { return process(nums, 0, nums.size() - 1, nums.size() - k); }
};
