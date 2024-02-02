#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations)
  {
    if (startFuel >= target)
    {
      return 0;
    }
    priority_queue<int> heap;
    // 包括初始油量 + 沿途加的油，能让你达到什么位置，to
    int to = startFuel;
    int cnt = 0;
    for (auto& station : stations)
    {
      int position = station[0];
      int fuel = station[1];
      if (to < position)
      {
        while (!heap.empty() && to < position)
        {
          to += heap.top();
          heap.pop();
          cnt++;
          if (to >= target)
          {
            return cnt;
          }
        }
        if (to < position)
        {
          return -1;
        }
      }
      heap.push(fuel);
    }
    // 走到这里，说明还没到达target
    // 如果还有油，看看能不能冲到target
    while (!heap.empty())
    {
      to += heap.top();
      heap.pop();
      cnt++;
      if (to >= target)
      {
        return cnt;
      }
    }
    return -1;
  }
};
