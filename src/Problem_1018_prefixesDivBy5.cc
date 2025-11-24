#include <vector>

using namespace std;

class Solution
{
 public:
  vector<bool> prefixesDivBy5(vector<int>& nums)
  {
    int n = nums.size();
    vector<bool> ans(n);
    int prefix = 0;
    for (int i = 0; i < n; i++)
    {
      prefix = ((prefix << 1) + nums[i]) % 5;
      ans[i] = prefix == 0;
    }
    return ans;
  }
};
