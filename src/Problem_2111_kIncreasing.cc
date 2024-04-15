#include <vector>

using namespace std;

// @sa 最长递增子序列 https://www.bilibili.com/video/BV1ne411D7CQ/
class Solution
{
 private:
  static const int MAX = 100001;
  vector<int> nums;
  vector<int> ends;

 public:
  int kIncreasing(vector<int>& arr, int k)
  {
    nums.resize(MAX, 0);
    ends.resize(MAX, 0);
    int n = arr.size();
    int ans = 0;
    // 把每一组的数拿出来，求最长不下降子序列，不在这个子序列的数即为需要修改的数
    // 比如 [4 2 2 4 2 6 6] 最长不下降子序列为 [2 2 2 6 6]
    // 只要把 2 个 4 改为 2 即可让 [2 2 2 2 2 6 6] 整个组为不下降组
    for (int i = 0, size; i < k; i++)
    {
      size = 0;
      // 把每一组的数字放入容器
      for (int j = i; j < n; j += k)
      {
        nums[size++] = arr[j];
      }
      // 当前组长度 - 当前组最长不下降子序列长度 = 当前组至少需要修改的数字个数
      ans += size - lengthOfNoDecreasing(size);
    }
    return ans;
  }

  int lengthOfNoDecreasing(int size)
  {
    int len = 0;
    for (int i = 0, find; i < size; i++)
    {
      find = bs(len, nums[i]);
      if (find == -1)
      {
        ends[len++] = nums[i];
      }
      else
      {
        ends[find] = nums[i];
      }
    }
    return len;
  }

  int bs(int len, int num)
  {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r)
    {
      m = (l + r) / 2;
      if (num < ends[m])
      {
        ans = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return ans;
  }
};
