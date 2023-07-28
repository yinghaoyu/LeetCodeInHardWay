#include <queue>
#include <vector>

using namespace std;

class KthLargest
{
  priority_queue<int, vector<int>, greater<int>> q;
  int k;

 public:
  KthLargest(int k, vector<int> &nums)
  {
    this->k = k;
    for (int i = 0; i < nums.size(); i++)
    {
      add(nums[i]);
    }
  }

  int add(int val)
  {
    q.push(val);
    if (q.size() > k)
    {
      q.pop();
    }
    return q.top();
  }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
