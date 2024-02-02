#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 贪心的思想，对于第 i 天，如果有若干的会议都可以在这一天开，
  // 那么我们肯定是让 endDay 小的会议先在这一天开才会使答案最优，
  // 因为 endDay 大的会议可选择的空间是比 endDay 小的多的，
  // 所以在满足条件的会议需要让 endDay 小的先开。

  int maxEvents(vector<vector<int>>& events)
  {
    int n = events.size();
    // events[i][0] : i号会议开始时间
    // events[i][1] : i号会议结束时间
    std::sort(events.begin(), events.end(), [](auto a, auto b) { return a[0] < b[0]; });
    int min = events[0][0];
    int max = events[0][1];
    for (int i = 1; i < n; i++)
    {
      max = std::max(max, events[i][1]);
    }
    // 小根堆 : 会议的结束时间
    priority_queue<int, vector<int>, greater<int>> heap;
    int i = 0;
    int ans = 0;
    // 时间往前推进
    for (int day = min; day <= max; day++)
    {
      while (i < n && events[i][0] == day)
      {
        // 当前 day 开始的会议加入
        heap.push(events[i++][1]);
      }
      while (!heap.empty() && heap.top() < day)
      {
        // 弹出过时的会议
        heap.pop();
      }
      if (!heap.empty())
      {
        // 选择会议结束时间最小的会议参加
        // 注意这里有pop操作，不会重复计算
        heap.pop();
        ans++;
      }
    }
    return ans;
  }
};
