#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> findRightInterval(vector<vector<int>>& intervals)
  {
    // 把所有的区间按左边界排序
    vector<std::pair<int, int>> startIntervals;
    int n = intervals.size();
    for (int i = 0; i < n; i++)
    {
      // i 也要参与排序，因为找的是往右最贴近的区间，当然是 i 越小越好
      startIntervals.emplace_back(intervals[i][0], i);
    }
    std::sort(startIntervals.begin(), startIntervals.end());

    vector<int> ans(n, -1);
    // 枚举所有区间的右边界
    for (int i = 0; i < n; i++)
    {
      // 找到第 1 个左边界 >= 当前区间右边界的区间
      auto it = lower_bound(startIntervals.begin(), startIntervals.end(),
                            std::make_pair(intervals[i][1], 0));
      if (it != startIntervals.end())
      {
        ans[i] = it->second;
      }
    }
    return ans;
  }
};
