#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// 此题是 Problem_0295_MedianFinder.cc 的进阶题

// 延迟删除
// 我们保证在任意操作 insert(num)，erase(num)，getMedian()
// 完成之后（或者说任意操作开始之前），small 和 large
// 的堆顶元素都是不需要被「延迟删除」的。
// 这样设计的好处在于：我们无需更改 getMedian() 的设计，只需要略加修改 insert(num) 即可。

class DualHeap
{
 private:
  // 大根堆，维护较小的一半元素
  priority_queue<int, vector<int>, less<int>> small;
  // 小根堆，维护较大的一半元素
  priority_queue<int, vector<int>, greater<int>> large;
  // 哈希表，记录「延迟删除」的元素，key 为元素，value 为需要删除的次数
  unordered_map<int, int> delayed;

  int k;
  // small 和 large 当前包含的元素个数，需要扣除被「延迟删除」的元素
  int smallSize, largeSize;

 public:
  DualHeap(int _k) : k(_k), smallSize(0), largeSize(0) {}

 private:
  // 不断地弹出 heap 的堆顶元素，并且更新哈希表
  template <typename T>
  void prune(T& heap)
  {
    while (!heap.empty())
    {
      int num = heap.top();
      if (delayed.count(num))
      {
        --delayed[num];
        if (!delayed[num])
        {
          delayed.erase(num);
        }
        heap.pop();
      }
      else
      {
        break;
      }
    }
  }

  // 调整 small 和 large 中的元素个数，使得二者的元素个数满足要求
  void makeBalance()
  {
    if (smallSize > largeSize + 1)
    {
      // small 比 large 元素多 2 个
      large.push(small.top());
      small.pop();
      --smallSize;
      ++largeSize;
      // small 堆顶元素被移除，需要进行 prune
      prune(small);
    }
    else if (smallSize < largeSize)
    {
      // large 比 small 元素多 1 个
      small.push(large.top());
      large.pop();
      ++smallSize;
      --largeSize;
      // large 堆顶元素被移除，需要进行 prune
      prune(large);
    }
  }

 public:
  void insert(int num)
  {
    if (small.empty() || num <= small.top())
    {
      small.push(num);
      ++smallSize;
    }
    else
    {
      large.push(num);
      ++largeSize;
    }
    makeBalance();
  }

  void erase(int num)
  {
    ++delayed[num];
    if (num <= small.top())
    {
      --smallSize;
      // 需要保证两个堆的堆顶都不是delayed存在的元素
      // 因此这个条件不能删除
      if (num == small.top())
      {
        prune(small);
      }
    }
    else
    {
      --largeSize;
      // 需要保证两个堆的堆顶都不是delayed存在的元素
      // 因此这个条件不能删除
      if (num == large.top())
      {
        prune(large);
      }
    }
    makeBalance();
  }

  double getMedian() { return k & 1 ? small.top() : ((double) small.top() + large.top()) / 2; }
};

class Solution
{
 public:
  vector<double> medianSlidingWindow(vector<int>& nums, int k)
  {
    DualHeap dh(k);
    for (int i = 0; i < k; ++i)
    {
      dh.insert(nums[i]);
    }
    vector<double> ans = {dh.getMedian()};
    for (int i = k; i < nums.size(); ++i)
    {
      dh.insert(nums[i]);
      dh.erase(nums[i - k]);
      ans.push_back(dh.getMedian());
    }
    return ans;
  }
};
