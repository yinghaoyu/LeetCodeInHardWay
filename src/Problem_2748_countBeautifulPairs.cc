#include <vector>

using namespace std;

class Solution
{
 public:
  int gcd(int a, int b) { return b != 0 ? gcd(b, a % b) : a; }

  int first(int x)
  {
    while (x / 10 != 0)
    {
      x /= 10;
    }
    return x;
  }

  int last(int x) { return x % 10; }

  int countBeautifulPairs(vector<int>& nums)
  {
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (gcd(first(nums[i]), last(nums[j])) == 1)
        {
          ans++;
        }
      }
    }
    return ans;
  }
};
