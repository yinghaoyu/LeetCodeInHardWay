#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

// https://leetcode.cn/problems/task-scheduler/solution/tong-zi-by-popopop/
// TODO: figout it out
class Solution
{
 public:
  int leastInterval(vector<char> &tasks, int n)
  {
    vector<int> cnt(256);
    // 出现最多次的任务，到底是出现了几次
    int maxCount = 0;
    for (auto &task : tasks)
    {
      cnt[task]++;
      maxCount = std::max(maxCount, cnt[task]);
    }
    // 有多少种任务，都出现最多次
    int maxKinds = 0;
    for (int task = 0; task < 256; task++)
    {
      if (cnt[task] == maxCount)
      {
        maxKinds++;
      }
    }
    // 砍掉最后一组剩余的任务数
    int taskExceptFinialTeam = tasks.size() - maxKinds;
    int spaces = (n + 1) * (maxCount - 1);
    int restSpaces = std::max(0, spaces - taskExceptFinialTeam);

    return tasks.size() + restSpaces;
  }
};

void testLeastInterval()
{
  Solution s;
  vector<char> t1 = {'A', 'A', 'A', 'B', 'B', 'B'};
  vector<char> t2 = {'A', 'A', 'A', 'B', 'B', 'B'};
  EXPECT_EQ_INT(8, s.leastInterval(t1, 2));
  EXPECT_EQ_INT(6, s.leastInterval(t2, 0));
  EXPECT_SUMMARY;
}

int main()
{
  testLeastInterval();
  return 0;
}
