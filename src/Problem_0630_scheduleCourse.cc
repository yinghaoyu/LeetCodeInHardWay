#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int scheduleCourse(vector<vector<int>>& courses)
  {
    // 将课程按结束时间从小到大排序
    std::sort(courses.begin(), courses.end(),
              [](const auto& left, const auto& right) { return left[1] < right[1]; });
    priority_queue<int> que;
    int total = 0;
    for (auto& course : courses)
    {
      int duration = course[0];
      int lastDay = course[1];
      // 有点像滑动窗口，lastDay 一定越来越大
      if (total + duration <= lastDay)
      {
        total += duration;
        que.push(duration);
      }
      else if (!que.empty() && que.top() > duration)
      {
        // 替换掉持续时间最长的课程，这样可以最大程度减少所耗用的时间
        total -= que.top() - duration;
        que.pop();
        que.push(duration);
      }
    }
    return que.size();
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
  vector<vector<int>> n2 = {{1, 2}};
  vector<vector<int>> n3 = {{3, 2}, {4, 3}};
  EXPECT_EQ_INT(3, s.scheduleCourse(n1));
  EXPECT_EQ_INT(1, s.scheduleCourse(n2));
  EXPECT_EQ_INT(0, s.scheduleCourse(n3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
