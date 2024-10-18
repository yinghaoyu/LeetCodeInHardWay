#include <vector>

using namespace std;

class Solution
{
 public:
  int minOperations(vector<int>& nums)
  {
    int n = nums.size();
    int ans = 0;
    // 从左到右遍历元素，遇到0就翻转nums[i] nums[i+1] nums[i+2]
    // 这种方式其实只对当前0元素遍历了一次，这已经是理论上最少的遍历翻转次数了
    // 即使有其他方式也能完成遍历翻转，也一定至少翻转遍历一次，才是最少次数
    for (int i = 0; i < n; i++)
    {
      if (nums[i] == 0)
      {
        if (i > n - 3)
        {
          // 如果后续少于3个元素，说明不能完成最后一次翻转
          return -1;
        }
        nums[i] ^= 1;
        nums[i + 1] ^= 1;
        nums[i + 2] ^= 1;
        ans++;
      }
    }
    return ans;
  }
};
