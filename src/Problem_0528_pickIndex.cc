#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 private:
  int sum;
  vector<int> pre;

 public:
  Solution(vector<int> &w)
  {
    int n = w.size();
    pre.resize(n);
    sum = 0;
    for (int i = 0; i < n; i++)
    {
      sum += w[i];
      if (i > 0)
      {
        pre[i] = pre[i - 1] + w[i];
      }
      else
      {
        pre[i] = w[i];
      }
    }
  }

  int pickIndex()
  {
    int x = random() % sum + 1;
    int left = 0;
    int right = pre.size() - 1;
    while (left < right)
    {
      int mid = (right - left) / 2 + left;
      if (pre[mid] < x)
      {
        left = mid + 1;
      }
      else
      {
        right = mid;
      }
    }
    return left;
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
