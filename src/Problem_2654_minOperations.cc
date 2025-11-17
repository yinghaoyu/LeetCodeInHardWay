#include <vector>

using namespace std;

class Solution
{
 public:
  int minOperations(vector<int>& nums)
  {
    int n = nums.size();
    int num1 = 0;
    int g = 0;
    for (int x : nums)
    {
      if (x == 1)
      {
        num1++;
      }
      g = gcd(g, x);
    }
    if (num1 > 0)
    {
      // 如果 nums 中已经存在 1，那我们可以让 1 和旁边的非 1 数字操作，
      // 最多只需做 n−num1 次操作
      return n - num1;
    }
    if (g > 1)
    {
      // 如果 nums 中所有数字的 gcd 是大于 1 的，
      // 那么无论如何都无法让数组全部变成 1
      return -1;
    }

    // 如果不属于以上两种情况，我们可以找到一个最小的区间，这个区间内所有数字的 gcd 是 1。
    // 假设这个区间长度是 len，那么由这些数字得到一个 1 所需的次数是 len−1；
    // 然后再由这个 1 使得其他数字都变为 1 所需的次数是 n−1。因此总共需要 len+n−2 次操作。

    int len = n;
    for (int i = 0; i < n; i++)
    {
      int g = 0;
      for (int j = i; j < n; j++)
      {
        g = gcd(g, nums[j]);
        if (g == 1)
        {
          len = min(len, j - i + 1);
          break;
        }
      }
    }
    return len + n - 2;
  }
};
