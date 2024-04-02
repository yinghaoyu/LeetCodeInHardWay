#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> smallestK(vector<int>& arr, int k)
  {
    if (k == 0)
    {
      return {};
    }
    // 大根堆
    priority_queue<int> q;
    for (int i = 0; i < k; i++)
    {
      // 先让 k 个元素进堆
      q.push(arr[i]);
    }
    for (int i = k; i < arr.size(); i++)
    {
      if (q.top() > arr[i])
      {
        // 大于堆顶的元素出堆，更小的元素进堆
        q.pop();
        q.push(arr[i]);
      }
    }
    vector<int> ans(k);
    while (!q.empty())
    {
      ans[--k] = q.top();
      q.pop();
    }
    return ans;
  }
};
