#include <vector>

using namespace std;

class Solution
{
 public:
  long long countCompleteDayPairs(vector<int>& hours)
  {
    long long ans = 0;
    vector<int> cnt(24);
    for (int h : hours)
    {
      // 先查询 cnt，再更新 cnt，因为题目要求 i < j
      // 如果先更新，再查询，就把 i = j 的情况也考虑进去了

      // 从左到右枚举当前数
      // 求前面的数跟当前的数相加 % 24 = 0 的个数
      // 累加得结果
      ans += cnt[(24 - h % 24) % 24];
      // 更新当前数的频次
      cnt[h % 24]++;
    }
    return ans;
  }
};
