#include <queue>
#include <vector>

using namespace std;

class MovingAverage
{
 private:
  queue<int> que;
  int size;
  double sum;

 public:
  MovingAverage(int size)
  {
    this->size = size;
    this->sum = 0;
  }

  double next(int val)
  {
    if (que.size() == size)
    {
      sum -= que.front();
      que.pop();
    }
    que.push(val);
    sum += val;
    return sum / que.size();
  }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
