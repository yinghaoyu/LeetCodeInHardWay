#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> sortArrayByParityII(vector<int>& nums)
  {
    int n = nums.size();
    for (int odd = 1, even = 0; odd < n && even < n;)
    {
      if (nums[n - 1] & 1)
      {
        std::swap(nums[odd], nums[n - 1]);
        odd += 2;
      }
      else
      {
        std::swap(nums[even], nums[n - 1]);
        even += 2;
      }
    }
    return nums;
  }
};
