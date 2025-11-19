#include <vector>

using namespace std;

class Solution
{
 public:
  int findFinalValue(vector<int>& nums, int original)
  {
    std::sort(nums.begin(), nums.end());
    for (int num : nums)
    {
      if (num == original)
      {
        original <<= 1;
      }
    }
    return original;
  }
};
