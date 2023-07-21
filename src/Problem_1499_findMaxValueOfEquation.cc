#include <deque>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 堆
  // 时间复杂度 n * log(n) 空间复杂度 O(n)
  int findMaxValueOfEquation1(vector<vector<int>> &points, int k)
  {
    int ans = INT32_MIN;
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>> heap;
    for (auto &point : points)
    {
      int x = point[0];
      int y = point[1];
      while (!heap.empty() && x - heap.top().second > k)
      {
        heap.pop();
      }
      if (!heap.empty())
      {
        ans = std::max(ans, x + y - heap.top().first);
      }
      heap.emplace(x - y, x);
    }
    return ans;
  }

  // 双端队列
  // 时间复杂度 O(n) 每个元素最多进入并离开队列一次
  // 空间复杂度 O(n)
  int findMaxValueOfEquation2(vector<vector<int>> &points, int k)
  {
    int ans = INT32_MIN;
    using PPI = pair<int, int>;
    deque<PPI> q;
    for (auto &point : points)
    {
      int x = point[0];
      int y = point[1];
      while (!q.empty() && x - q.front().second > k)
      {
        q.pop_front();
      }
      if (!q.empty())
      {
        ans = std::max(ans, x + y + q.front().first);
      }
      // 弹出队列末端小于等于当前 y - x 的元素
      // 保证双端队列递减
      while (!q.empty() && y - x >= q.back().first)
      {
        q.pop_back();
      }
      q.emplace_back(y - x, x);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> p1 = {{1, 3}, {2, 0}, {5, 10}, {6, -10}};
  vector<vector<int>> p2 = {{0, 0}, {3, 0}, {9, 2}};
  EXPECT_EQ_INT(4, s.findMaxValueOfEquation1(p1, 1));
  EXPECT_EQ_INT(3, s.findMaxValueOfEquation1(p2, 3));
  EXPECT_EQ_INT(4, s.findMaxValueOfEquation2(p1, 1));
  EXPECT_EQ_INT(3, s.findMaxValueOfEquation2(p2, 3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
