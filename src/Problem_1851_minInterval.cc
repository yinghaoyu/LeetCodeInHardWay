#include <algorithm>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 扫描线原理
class Solution
{
 public:
  vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries)
  {
    vector<int> idxs(queries.size());
    for (int i = 0; i < queries.size(); i++)
    {
      idxs[i] = i;
    }

    // 索引按 queries[i]  从小到大排序
    // 这样遍历idxs时，就有谁 queries[i] 小，谁先处理，符合扫描线，在x轴从左到右
    // 使用idxs数组是为了保留编号，方便填答案
    std::sort(idxs.begin(), idxs.end(),
              [&](int i, int j) -> bool { return queries[i] < queries[j]; });

    // 区间按开始从小到大排序
    std::sort(intervals.begin(), intervals.end(),
              [](vector<int>& l, vector<int>& r) { return l[0] < r[0]; });

    // 大根堆
    priority_queue<vector<int>> que;

    // 初始化为-1
    vector<int> ans(queries.size(), -1);
    int i = 0;

    // 从小到大依次遍历 queries[i]
    for (auto& idx : idxs)
    {
      // 由于区间按开始从小到大排序，那么先检查这个区间是否包含当前的扫描线 x = queries[idx]
      // 包含这个扫描线的区间全部进堆
      while (i < intervals.size() && intervals[i][0] <= queries[idx])
      {
        int len = intervals[i][1] - intervals[i][0] + 1;
        // 取负号，是为了让大根堆达到小根堆的效果，简化C++代码
        // 最短的区间在堆顶
        que.push({-len, intervals[i][0], intervals[i][1]});
        i++;
      }
      while (!que.empty() && que.top()[2] < queries[idx])
      {
        // 当前扫描线 x = queries[idx] 在这些区间的右边，说明这些区间都已经过期了
        // 注意，这里的-que.top()[0]是最小的，而que.top()[2]不一定是最小的
        // 可能符合条件的非堆顶区间(脏数据)在这轮没删除，也没关系
        // 在后面一定会被删除
        que.pop();
      }
      if (!que.empty())
      {
        // 存在区间，就把区间最小的左端点，填答案
        ans[idx] = -que.top()[0];
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 4}, {2, 4}, {3, 6}, {4, 4}};
  vector<vector<int>> n2 = {{2, 3}, {2, 5}, {1, 8}, {20, 25}};
  vector<int> q1 = {2, 3, 4, 5};
  vector<int> q2 = {2, 19, 5, 22};
  vector<int> o1 = {3, 3, 1, 4};
  vector<int> o2 = {2, -1, 4, 6};
  EXPECT_TRUE(o1 == s.minInterval(n1, q1));
  EXPECT_TRUE(o2 == s.minInterval(n2, q2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
