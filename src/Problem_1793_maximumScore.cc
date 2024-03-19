#include <stack>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 单调栈
  int maximumScore1(vector<int>& nums, int k)
  {
    int n = nums.size();
    vector<int> left(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
      // 单调递增栈
      while (!st.empty() && nums[i] <= nums[st.top()])
      {
        st.pop();
      }
      if (!st.empty())
      {
        left[i] = st.top();
      }
      st.push(i);
    }
    vector<int> right(n, n);
    st = stack<int>();
    for (int i = n - 1; i >= 0; i--)
    {
      while (!st.empty() && nums[i] <= nums[st.top()])
      {
        st.pop();
      }
      if (!st.empty())
      {
        right[i] = st.top();
      }
      st.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      int h = nums[i];
      // 在 i 左侧的小于 h 的最近元素的下标 left[i]
      int l = left[i];
      // 在 p 右侧的小于 h 的最近元素的下标 right[i]
      int r = right[i];
      // 注意 (l, k) 是开区间
      if (l < k && k < r)
      {
        ans = std::max(ans, h * (r - l - 1));
      }
    }
    return ans;
  }

  // 双指针
  // TODO: figure it out.
  int maximumScore2(vector<int>& nums, int k)
  {
    int n = nums.size();
    int left = k - 1;
    int right = k + 1;
    int ans = 0;
    for (int i = nums[k];; i--)
    {
      while (left >= 0 && nums[left] >= i)
      {
        left--;
      }
      while (right < n && nums[right] >= i)
      {
        right++;
      }
      ans = std::max(ans, (right - left + 1) * i);
      if (left == -1 && right == n)
      {
        break;
      }
    }
    return ans;
  }
};
