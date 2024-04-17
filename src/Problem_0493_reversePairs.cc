#include <vector>

using namespace std;

class Solution
{
 public:
  int merge(vector<int>& arr, int l, int m, int r)
  {
    // 统计
    int ans = 0;
    int winL = m;
    int winR = r;
    while (l <= winL && m < winR)
    {
      while (m < winR && (long long) arr[winL] <= 2 * (long long) arr[winR])
      {
        winR--;
      }
      ans += winR - m;
      winL--;
    }
    // 归并
    int len = r - l + 1;
    vector<int> help(len);
    int p1 = m;
    int p2 = r;
    int i = len - 1;
    while (l <= p1 && m < p2)
    {
      help[i--] = arr[p1] > arr[p2] ? arr[p1--] : arr[p2--];
    }
    while (l <= p1)
    {
      help[i--] = arr[p1--];
    }
    while (m < p2)
    {
      help[i--] = arr[p2--];
    }
    for (int i = 0; i < len; i++)
    {
      arr[l + i] = help[i];
    }
    return ans;
  }

  int f(vector<int>& arr, int l, int r)
  {
    if (l == r)
    {
      return 0;
    }
    int m = (r - l) / 2 + l;
    return f(arr, l, m) + f(arr, m + 1, r) + merge(arr, l, m, r);
  }

  int reversePairs(vector<int>& nums) { return f(nums, 0, nums.size() - 1); }
};
