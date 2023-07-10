#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder
{
 private:
  priority_queue<int, vector<int>, std::less<int>> min;     // 大根堆
  priority_queue<int, vector<int>, std::greater<int>> max;  // 小根堆
 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num)
  {
    if (min.empty() || num < min.top())
    {
      min.push(num);
      if (min.size() > max.size() + 1)
      {
        int cur = min.top();
        min.pop();
        max.push(cur);
      }
    }
    else
    {
      max.push(num);
      if (max.size() > min.size())
      {
        int cur = max.top();
        max.pop();
        min.push(cur);
      }
    }
  }

  double findMedian()
  {
    if (min.size() > max.size())
    {
      return min.top();
    }
    else
    {
      return (min.top() + max.top()) / 2.0;
    }
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
