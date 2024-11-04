#include <cmath>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 双指针
  bool judgeSquareSum(int c)
  {
    long left = 0;
    long right = sqrt(c);
    while (left <= right)
    {
      long sum = left * left + right * right;
      if (sum == c)
      {
        return true;
      }
      else if (sum > c)
      {
        right--;
      }
      else
      {
        left++;
      }
    }
    return false;
  }
};
