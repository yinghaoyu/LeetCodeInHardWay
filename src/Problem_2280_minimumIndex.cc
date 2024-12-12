#include <vector>

using namespace std;

// 摩尔投票
// 划分左右使其水王数相同
// 给定一个大小为n的数组nums
// 水王数是指在数组中出现次数大于n/2的数
// 返回其中的一个划分点下标，使得左侧水王数等于右侧水王数
// 如果数组不存在这样的划分返回-1
// 测试链接 : https://leetcode.cn/problems/minimum-index-of-a-valid-split/
class Solution
{
 public:
  int minimumIndex(vector<int>& nums)
  {
    int candidate = 0;
    int hp = 0;
    for (int num : nums)
    {
      if (hp == 0)
      {
        candidate = num;
        hp = 1;
      }
      else if (candidate == num)
      {
        hp++;
      }
      else
      {
        hp--;
      }
    }
    hp = 0;
    for (int num : nums)
    {
      if (num == candidate)
      {
        hp++;
      }
    }
    // 如果左侧的水王数和右侧的水王数一样，那么这个水王数一定是全局水王数
    int n = nums.size();
    // lc : 水王数左侧出现的词频
    // rc : 水王数右侧出现的词频
    for (int i = 0, lc = 0, rc = hp; i < n - 1; i++)
    {
      if (nums[i] == candidate)
      {
        lc++;
        rc--;
      }
      // 左侧的词频 > 左侧的一半 并且 右侧的词频 > 右侧的一半
      if (lc > (i + 1) / 2 && rc > (n - i - 1) / 2)
      {
        // 找到了划分点直接返回
        return i;
      }
    }
    // 不存在这样的划分点返回-1
    return -1;
  }
};
