#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> applyOperations(vector<int> &nums)
  {
    int n = nums.size();
    for (int i = 0, j = 0; i < n; ++i)
    {
      if (i + 1 < n && nums[i] == nums[i + 1])
      {
        nums[i] *= 2;
        nums[i + 1] = 0;
      }
      if (nums[i] != 0)
      {
        // i++ 一定比 j++ 快
        swap(nums[i], nums[j++]);
      }
    }

    return nums;
  }
};
