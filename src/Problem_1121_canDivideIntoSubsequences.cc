#include <vector>

using namespace std;

class Solution
{
 public:
  bool canDivideIntoSubsequences(vector<int>& nums, int k)
  {
    int cnt = 1;
    // maxCnt : 最大词频
    int maxCnt = 1;
    // 在有序数组中，求某个数的最大词频
    for (int i = 1; i < nums.size(); i++)
    {
      if (nums[i - 1] != nums[i])
      {
        maxCnt = std::max(maxCnt, cnt);
        cnt = 1;
      }
      else
      {
        cnt++;
      }
    }
    maxCnt = std::max(maxCnt, cnt);
    // 向下取整如果满足 >= k
    // 那么所有的递增子序列长度一定 >= k
    return nums.size() / maxCnt >= k;
  }
};
