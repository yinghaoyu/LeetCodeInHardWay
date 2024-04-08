#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k)
  {
    unordered_map<int, int> lastIdx;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      if (lastIdx.count(nums[i]) && i - lastIdx[nums[i]] <= k)
      {
        return true;
      }
      lastIdx[nums[i]] = i;
    }
    return false;
  }
};
