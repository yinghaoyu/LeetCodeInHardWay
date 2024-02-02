#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 private:
  class greater
  {
   public:
    bool operator()(pair<int, int>& lhs, pair<int, int>& rhs) { return lhs.second > rhs.second; }
  };

  class less
  {
   public:
    bool operator()(pair<int, int>& lhs, pair<int, int>& rhs) { return lhs.first < rhs.first; }
  };

 public:
  int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital)
  {
    int n = profits.size();
    // 需要的启动金小根堆
    // 代表被锁住的项目
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater> heap1;
    // 利润大根堆
    // 代表被解锁的项目
    priority_queue<pair<int, int>, vector<pair<int, int>>, less> heap2;

    for (int i = 0; i < n; i++)
    {
      heap1.push({profits[i], capital[i]});
    }
    while (k > 0)
    {
      while (!heap1.empty() && heap1.top().second <= w)
      {
        heap2.push(heap1.top());
        heap1.pop();
      }
      if (heap2.empty())
      {
        break;
      }
      w += heap2.top().first;
      heap2.pop();
      k--;
    }
    return w;
  }
};
