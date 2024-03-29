#include <functional>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder
{
 public:
  MedianFinder() {}

  // 较小的一半放在大根堆 max，较大的一半放在小根堆 min
  // 如果 max 为空，先进 max
  // 如果num <= max.top() 进 max，否则进 min
  // 如果 |max.size() - min.size()| == 2，则进行调整
  void addNum(int num)
  {
    if (max.empty())
    {
      max.push(num);
    }
    else
    {
      if (max.top() >= num)
      {
        max.push(num);
      }
      else
      {
        min.push(num);
      }
    }
    balance();
  }

  double findMedian()
  {
    if (max.size() == min.size())
    {
      return (double) (max.top() + min.top()) / 2;
    }
    else
    {
      return max.size() > min.size() ? max.top() : min.top();
    }
  }

  void balance()
  {
    if (max.size() == min.size() + 2)
    {
      min.push(max.top());
      max.pop();
    }
    if (max.size() == min.size() - 2)
    {
      max.push(min.top());
      min.pop();
    }
  }

 private:
  // 两个优先级队列记录
  // 一个记录 >= 中位数的数
  // 一个记录 <= 中位数的数
  priority_queue<int, vector<int>, less<int>> max;
  priority_queue<int, vector<int>, greater<int>> min;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
