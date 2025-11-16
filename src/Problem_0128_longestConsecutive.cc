#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 新元素+1或-1碰到的元素一定是一个已记载序列的已知左边界或者已知右边界
  // 所以只需要保证已知左边界元素和已知右边界元素的左右边界记录正确即可
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

void testLongestConsecutive()
{
  Solution s;
  vector<int> n1 = {100, 4, 200, 1, 3, 2};
  vector<int> n2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  vector<int> n3 = {1, 0, 1, 2};
  EXPECT_EQ_INT(4, s.longestConsecutive(n1));
  EXPECT_EQ_INT(9, s.longestConsecutive(n2));
  EXPECT_EQ_INT(3, s.longestConsecutive(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestConsecutive();
  return 0;
}
