#include <pthread.h>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  class cmp
  {
   public:
    bool operator()(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) { return lhs.first < rhs.first; }
  };
  vector<vector<int>> merge(vector<vector<int>> &intervals)
  {
    priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, cmp> q;
    vector<vector<int>> ans;
    for (auto &e : intervals)
    {
      q.push({e[0], e[1]});
    }
    while (!q.empty())
    {
      auto [start, end] = q.top();
      q.pop();
      while (!q.empty() && q.top().first <= end)
      {
        // 这里取最大值是为了避免子区间的出现
        // [1, 5] [2, 4]
        // 还是取[1, 5]
        end = std::max(end, q.top().second);
        q.pop();
      }
      ans.push_back({start, end});
    }
    return ans;
  }
};

bool isVectorEqual(vector<vector<int>> a, vector<vector<int>> b)
{
  if (a.size() != b.size() || a[0].size() != b[0].size())
  {
    return false;
  }
  for (int i = 0; i < a.size(); i++)
  {
    for (int j = 0; j < a[0].size(); j++)
    {
      if (a[i][j] != b[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

void testMerge()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
  vector<vector<int>> o1 = {{1, 6}, {8, 10}, {15, 18}};
  vector<vector<int>> n2 = {{1, 4}, {4, 5}};
  vector<vector<int>> o2 = {{1, 5}};
  EXPECT_TRUE(isVectorEqual(o1, s.merge(n1)));
  EXPECT_TRUE(isVectorEqual(o2, s.merge(n2)));
  EXPECT_SUMMARY;
}

int main()
{
  testMerge();
  return 0;
}
