#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Soultion
{
 public:
  int connectSticks(vector<int>& arr)
  {
    // 小根堆
    priority_queue<int, vector<int>, std::greater<int>> heap;
    for (int i = 0; i < arr.size(); i++)
    {
      heap.push(arr[i]);
    }
    int sum = 0;
    int cur = 0;
    while (heap.size() > 1)
    {
      cur = heap.top();
      heap.pop();
      cur += heap.top();
      heap.pop();
      sum += cur;
      heap.push(cur);
    }
    return sum;
  }
};
