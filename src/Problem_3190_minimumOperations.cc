#include <vector>

using namespace std;

class Solution
{
 public:
  int minimumOperations(vector<int>& nums)
  {
    int ans = 0;
    for (int num : nums)
    {
      int mod = num % 3;
      ans += std::min(mod, 3 - mod);
    }
    return ans;
  }
};
