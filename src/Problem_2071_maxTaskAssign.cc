#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
   // TODO: figure it out
  int maxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills, int strength)
  {
    int n = tasks.size(), m = workers.size();
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());

    auto check = [&](int mid) -> bool {
      int p = pills;
      deque<int> ws;
      int ptr = m - 1;
      // 从大到小枚举每一个任务
      for (int i = mid - 1; i >= 0; --i)
      {
        while (ptr >= m - mid && workers[ptr] + strength >= tasks[i])
        {
          ws.push_front(workers[ptr]);
          --ptr;
        }
        if (ws.empty())
        {
          return false;
        }
        // 如果双端队列中最大的元素大于等于 tasks[i]
        else if (ws.back() >= tasks[i])
        {
          ws.pop_back();
        }
        else
        {
          if (!p)
          {
            return false;
          }
          --p;
          ws.pop_front();
        }
      }
      return true;
    };

    int left = 1, right = min(m, n), ans = 0;
    while (left <= right)
    {
      int mid = (left + right) / 2;
      if (check(mid))
      {
        ans = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return ans;
  }
};

void testMaxTaskAssign()
{
  Solution s;
  vector<int> t1 = {3, 2, 1};
  vector<int> w1 = {0, 3, 3};

  vector<int> t2 = {5, 4};
  vector<int> w2 = {0, 0, 0};

  vector<int> t3 = {10, 15, 30};
  vector<int> w3 = {0, 10, 10, 10, 10};

  EXPECT_EQ_INT(3, s.maxTaskAssign(t1, w1, 1, 1));
  EXPECT_EQ_INT(1, s.maxTaskAssign(t2, w2, 1, 5));
  EXPECT_EQ_INT(2, s.maxTaskAssign(t3, w3, 3, 10));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxTaskAssign();
  return 0;
}
