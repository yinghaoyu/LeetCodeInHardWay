#include <vector>

using namespace std;

class Solution
{
 public:
  // 题设条件数组有序，那么一定有
  // 左边的数一定 < 当前数的下标index，右边的数一定 > 当前数的下标index
  int f(vector<int>& nums, int left, int right)
  {
    if (left > right)
    {
      return -1;
    }
    int mid = (right - left) / 2 + left;
    int lres = f(nums, left, mid - 1);
    if (lres != -1)
    {
      // 由于有多数满足条件，我们要找第一个
      // 所以如果左边能找到，则直接返回
      return lres;
    }
    else if (nums[mid] == mid)
    {
      // 左边没找到，再看看中点
      return mid;
    }
    // 最后才看右边
    return f(nums, mid + 1, right);
  }

  int findMagicIndex(vector<int>& nums) { return f(nums, 0, nums.size() - 1); }
};
