#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 方法一：利用 priority_queue
  vector<int> getLeastNumbers1(vector<int> &arr, int k)
  {
    vector<int> ans;
    if (k == 0)
    {
      return ans;
    }
    priority_queue<int> que;
    for (int i = 0; i < k; i++)
    {
      // 建立 k 个元素的大根堆
      que.push(arr[i]);
    }
    for (int i = k; i < arr.size(); i++)
    {
      if (arr[i] < que.top())
      {
        // < 大根堆堆顶时，堆顶出，当前元素入堆
        que.pop();
        que.push(arr[i]);
      }
    }
    for (int i = 0; i < k; i++)
    {
      int cur = que.top();
      que.pop();
      ans.push_back(cur);
    }
    return ans;
  }

  // 自建堆
  vector<int> getLeastNumbers2(vector<int> &arr, int k)
  {
    vector<int> ans;
    if (k == 0)
    {
      return ans;
    }
    int n = arr.size();
    for (int i = n - 1; i >= 0; i--)
    {
      // 自底向上建堆
      heapify(arr, i, n);
    }

    int size = n;
    std::swap(arr[0], arr[--size]);
    int count = 1;

    while (size > 0 && count < k)
    {
      heapify(arr, 0, size);
      std::swap(arr[0], arr[--size]);
      count++;
    }
    for (int i = n - 1; i > n - 1 - k; i--)
    {
      ans.push_back(arr[i]);
    }
    return ans;
  }

  void heapify(vector<int> &arr, int index, int size)
  {
    int left = index * 2 + 1;
    while (left < size)
    {
      int smallest = left;
      if (left + 1 < size)
      {
        smallest = arr[smallest] < arr[left + 1] ? smallest : left + 1;
      }
      smallest = arr[index] < arr[smallest] ? index : smallest;
      if (smallest == index)
      {
        break;
      }
      std::swap(arr[smallest], arr[index]);
      index = smallest;
      left = index * 2 + 1;
    }
  }
};
