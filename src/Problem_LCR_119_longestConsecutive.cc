#include <unordered_map>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/longest-consecutive-sequence/
// @sa Problem_0128_longestConsecutive.cc
class Solution
{
 public:
  int longestConsecutive(vector<int>& nums)
  {
    // key表示num，value表示num所在连续区间的长度
    unordered_map<int, int> map;
    int len = 0;
    for (auto& num : nums)
    {
      // 当map中不包含num，也就是num第一次出现
      if (!map.count(num))
      {
        map.emplace(num, 1);
        // preLen为num-1所在连续区间的长度，更进一步理解为：左连续区间的长度
        int preLen = map.count(num - 1) ? map.at(num - 1) : 0;
        // posLen为num+1所在连续区间的长度，更进一步理解为：右连续区间的长度
        int posLen = map.count(num + 1) ? map.at(num + 1) : 0;
        // 当前连续区间的总长度
        int all = preLen + posLen + 1;
        // 更新当前连续区间左边界和右边界对应的区间长度
        map[num - preLen] = all;
        map[num + posLen] = all;
        len = std::max(len, all);
      }
    }
    return len;
  }
};
