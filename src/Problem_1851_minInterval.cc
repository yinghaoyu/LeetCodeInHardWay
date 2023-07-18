#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> minInterval(vector<vector<int>> &intervals, vector<int> &queries)
  {
    vector<int> idxs(queries.size());
    for (int i = 0; i < queries.size(); i++)
    {
      idxs[i] = i;
    }
    // 索引按 queries[i]  从小到大排序
    std::sort(idxs.begin(), idxs.end(), [&](int i, int j) -> bool { return queries[i] < queries[j]; });
    // 区间按 left 从小到大排序
    std::sort(intervals.begin(), intervals.end(), [](vector<int> &l, vector<int> &r) { return l[0] < r[0]; });
    // 大根堆
    priority_queue<vector<int>> que;
    vector<int> ans(queries.size(), -1);
    int i = 0;
    for (auto &idx : idxs)
    {
      while (i < intervals.size() && intervals[i][0] <= queries[idx])
      {
        int len = intervals[i][1] - intervals[i][0] + 1;
        // 堆顶 -len 最大， 对应 len 最小
        que.push({-len, intervals[i][0], intervals[i][1]});
        i++;
      }
      while (!que.empty() && que.top()[2] < queries[idx])
      {
        // 淘汰范围过小的区间
        que.pop();
      }
      if (!que.empty())
      {
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
