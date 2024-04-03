#include <functional>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder
{
 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  // [...4 5 6] [7 8 9 ...]
  // 对于一串数的中位数，左边的数都小于中位数，右边的数都大于中位数
  // 把一串数放在两个堆内，
  // 前面的堆是大根堆，这样堆顶是最接近中位数的
  // 后面的堆是小根堆，这样堆顶也是最接近中位数的
  void addNum(int num)
  {
    // num 小于前面的堆顶，就存到前面的堆
    if (qA.empty() || num < qA.top())
    {
      qA.push(num);
      // 如果前面的堆比后面的堆多出了不止一个数
      // 就把前面的堆顶移动到后面的堆
      if (qA.size() > qB.size() + 1)
      {
        int cur = qA.top();
        qA.pop();
        qB.push(cur);
      }
    }
    else
    {
      // num 大于前面的堆顶，就存到后面的堆
      qB.push(num);
      if (qB.size() > qA.size())
      {
        int cur = qB.top();
        qB.pop();
        qA.push(cur);
      }
    }
  }

  double findMedian()
  {
    if (qA.size() > qB.size())
    {
      // 总共元素是奇数个
      return qA.top();
    }
    else
    {
      // 偶数个
      return (qA.top() + qB.top()) / 2.0;
    }
  }

  // 大根堆
  priority_queue<int, vector<int>, less<int>> qA;

  // 小根堆
  priority_queue<int, vector<int>, greater<int>> qB;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
