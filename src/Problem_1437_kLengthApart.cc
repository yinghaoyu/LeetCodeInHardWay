#include <vector>

using namespace std;

class Solution
{
 public:
  bool kLengthApart(vector<int>& nums, int k)
  {
    int last1 = -1;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      if (nums[i] == 1)
      {
        if (last1 != -1 && i - last1 - 1 < k)
        {
          return false;
        }
        last1 = i;
      }
    }
    return true;
  }
};
