#include <vector>

using namespace std;

class Solution
{
 public:
  int maximumCount(vector<int>& nums)
  {
    int n = nums.size();
    int idx1 = nearLeftSearch(nums, 0);
    int idx2 = nearLeftSearch(nums, 1);
    return std::max(idx1, n - idx2);
  }

  int nearLeftSearch(vector<int>& arr, int target)
  {
    int l = 0;
    int r = arr.size();
    while (l < r)
    {
      int m = (r - l) / 2 + l;
      if (target <= arr[m])
      {
        r = m;
      }
      else
      {
        l = m + 1;
      }
    }
    return r;
  }
};
