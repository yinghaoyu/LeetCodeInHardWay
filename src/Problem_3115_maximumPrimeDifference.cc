#include <vector>

using namespace std;

class Solution
{
 public:
  bool isPrime(int x)
  {
    if (x == 1)
    {
      return false;
    }
    for (int i = 2; i * i <= x; i++)
    {
      if (x % i == 0)
      {
        return false;
      }
    }
    return true;
  }

  int maximumPrimeDifference(vector<int>& nums)
  {
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r && !isPrime(nums[l]))
    {
      l++;
    }
    while (r >= l && !isPrime(nums[r]))
    {
      r--;
    }
    return r - l;
  }
};
