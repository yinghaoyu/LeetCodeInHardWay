#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k)
  {
    int m = nums1.size();
    int n = nums2.size();
    vector<int> ans(k, 0);
    // 当结果全从 nums2 取，那么 nums1 至少取 std::max(0, k - n) 个
    int start = std::max(0, k - n);
    // 当结果全从 nums1 取，那么 nums1 至多取 std::max(k, m) 个
    int end = std::min(k, m);
    // 尝试所有 nums1 取的情况
    for (int i = start; i <= end; i++)
    {
      // 从 nums1 取 i 个元素
      vector<int> s1 = getMaxSubSequence(nums1, i);
      // 从 nums2 取 k - i 个元素
      vector<int> s2 = getMaxSubSequence(nums2, k - i);
      // 合并两个序列
      vector<int> cur = merge(s1, s2);
      // 比较谁更大，保留谁
      if (compare(cur, 0, ans, 0) > 0)
      {
        ans = std::move(cur);
      }
    }
    return ans;
  }

  // 获取数组内最大的序列，这个序列总共 k 个元素
  vector<int> getMaxSubSequence(vector<int>& arr, int k)
  {
    int n = arr.size();
    vector<int> stk(k, 0);
    int top = -1;
    int remain = n - k;
    for (int i = 0; i < n; i++)
    {
      int num = arr[i];
      while (top >= 0 && stk[top] < num && remain > 0)
      {
        top--;
        // 每次出栈，remain--，这样保证当 remain == 0时，stk 里面的元素有 k 个
        remain--;
      }
      if (top < k - 1)
      {
        stk[++top] = num;
      }
      else
      {
        // 栈满了，剩余的元素也进不了栈
        remain--;
      }
    }
    return stk;
  }

  vector<int> merge(vector<int>& s1, vector<int>& s2)
  {
    int n = s1.size();
    int m = s2.size();
    if (n == 0)
    {
      return s2;
    }
    if (m == 0)
    {
      return s1;
    }
    int total = n + m;
    vector<int> ans(total);
    int idx1 = 0;
    int idx2 = 0;
    for (int i = 0; i < total; i++)
    {
      if (compare(s1, idx1, s2, idx2) > 0)
      {
        ans[i] = s1[idx1++];
      }
      else
      {
        ans[i] = s2[idx2++];
      }
    }
    return ans;
  }

  // 比较两个子序列，分别从 idx1 和 idx2 开始
  int compare(vector<int>& s1, int idx1, vector<int>& s2, int idx2)
  {
    int n = s1.size();
    int m = s2.size();
    while (idx1 < n && idx2 < m)
    {
      int diff = s1[idx1] - s2[idx2];
      if (diff != 0)
      {
        return diff;
      }
      idx1++;
      idx2++;
    }
    // 比较剩余长度
    return (n - idx1) - (m - idx2);
  }
};
