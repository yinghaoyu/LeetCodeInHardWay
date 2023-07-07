#include <cstdint>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findCrossingTime(int n, int k, vector<vector<int>> &time)
  {
    auto wait_priority_cmp = [&](int x, int y)
    {
      // 时间总和越高，效率越低，优先级越低
      // 时间总和一样，id 越大，效率越低
      int timeX = time[x][0] + time[x][2];
      int timeY = time[y][0] + time[y][2];
      return timeX != timeY ? timeX < timeY : x < y;
    };
    // 在左侧等待
    priority_queue<int, vector<int>, decltype(wait_priority_cmp)> wait_left(wait_priority_cmp);
    // 在右侧等待
    priority_queue<int, vector<int>, decltype(wait_priority_cmp)> wait_right(wait_priority_cmp);
    using PII = std::pair<int, int>;  // 完成任务的时刻
    // 在左侧工作，放下所选的箱子
    priority_queue<PII, vector<PII>, std::greater<PII>> work_left;
    // 在右侧工作，放下所选的箱子
    priority_queue<PII, vector<PII>, std::greater<PII>> work_right;

    int remain = n;
    int curTime = 0;

    for (int i = 0; i < k; i++)
    {
      // 开始时，有 k 个工人在左边等待
      wait_left.push(i);
    }

    while (remain > 0 || !work_right.empty() || !wait_right.empty())
    {
      // 左侧的工人完成工作，则进入等待
      while (!work_left.empty() && work_left.top().first <= curTime)
      {
        wait_left.push(work_left.top().second);
        work_left.pop();
      }
      // 右侧的工人完成工作，则进入等待
      while (!work_right.empty() && work_right.top().first <= curTime)
      {
        wait_right.push(work_right.top().second);
        work_right.pop();
      }
      if (!wait_right.empty())
      {
        // 右边等待的工人可以先过桥
        int id = wait_right.top();
        wait_right.pop();
        curTime += time[id][2];  // 改为过桥后的时刻
        work_left.push({curTime + time[id][3], id});
      }
      else if (remain > 0 && !wait_left.empty())
      {
        // 如果还有箱子没搬，左边等待的工人可以过桥
        int id = wait_left.top();
        wait_left.pop();
        curTime += time[id][0];  // 改为过桥后的时刻
        work_right.push({curTime + time[id][1], id});
        remain--;
      }
      else
      {
        // 没人过桥，过渡到左边和右边最早完成任务的时刻
        int nextTime = INT32_MAX;
        if (!work_left.empty())
        {
          nextTime = std::min(nextTime, work_left.top().first);
        }
        if (!work_right.empty())
        {
          nextTime = std::min(nextTime, work_right.top().first);
        }
        if (nextTime != INT32_MAX)
        {
          curTime = std::max(nextTime, curTime);
        }
      }
    }
    return curTime;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> t1 = {{1, 1, 2, 1}, {1, 1, 3, 1}, {1, 1, 4, 1}};
  vector<vector<int>> t2 = {{1, 9, 1, 8}, {10, 10, 10, 10}};
  EXPECT_EQ_INT(6, s.findCrossingTime(1, 3, t1));
  EXPECT_EQ_INT(50, s.findCrossingTime(3, 2, t2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
