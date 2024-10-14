#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  // 首先对于或操作，或的数越多，值越大，符合单调性，因此可以考虑滑动窗口解决
  int minimumDifference(vector<int>& nums, int k)
  {
    int n = nums.size();
    vector<int> bits_max_pos(31, -1);
    // 数的位置 i (0 <= i < n)，以及哪一位上有 1
    // 比如 nums = (7, 1)
    // 那么对于 nums[0]=7 来说，对应二进制 0111，
    // 存储在 bits_max_pos 为 (0, 0) (0, 1) (0, 2)
    //     对于 nums[1]=1 来说，对应二进制 0001，
    // 存储在 bits_max_pos 为 (1, 0)
    vector<pair<int, int>> pos_to_bit;
    int res = INT_MAX;
    // 遍历每个数
    for (int i = 0; i < n; i++)
    {
      // 遍历每一位
      for (int j = 0; j <= 30; j++)
      {
        if (nums[i] >> j & 1)
        {
          // 统计哪一位是 1，记录当前数的位置 i
          // 随着每个数的统计 bits_max_pos 没有清空，是叠加更新的
          bits_max_pos[j] = i;
        }
      }
      pos_to_bit.clear();
      for (int j = 0; j <= 30; j++)
      {
        if (bits_max_pos[j] != -1)
        {
          // 记录第 i 个数在 j 位上有 1
          pos_to_bit.push_back(make_pair(bits_max_pos[j], j));
        }
      }
      // 从大到小排序
      sort(pos_to_bit.begin(), pos_to_bit.end(), greater<pair<int, int>>());
      int val = 0;
      for (int j = 0, p = 0; j < pos_to_bit.size();)
      {
        while (j < pos_to_bit.size() && pos_to_bit[j].first == pos_to_bit[p].first)
        {
          val |= 1 << pos_to_bit[j].second;
          j++;
        }
        res = min(res, abs(val - k));
        p = j;
      }
    }
    return res;
  }
};
