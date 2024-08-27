#include <unordered_map>
#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  int medianOfUniquenessArray(vector<int>& nums)
  {
    int n = nums.size();
    long long k = ((long long) n * (n + 1) / 2 + 1) / 2;

    auto check = [&](int upper)
    {
      long long cnt = 0;
      int l = 0;
      unordered_map<int, int> freq;
      for (int r = 0; r < n; r++)
      {
        freq[nums[r]]++;  // 移入右端点
        while (freq.size() > upper)
        {
          // 窗口内元素过多
          int out = nums[l++];
          if (--freq[out] == 0)
          {
            // 移出左端点
            freq.erase(out);
          }
        }
        cnt += r - l + 1;  // 右端点固定为 r 时，有 r-l+1 个合法左端点
        if (cnt >= k)
        {
          return true;
        }
      }
      return false;
    };

    int left = 0, right = n;
    while (left + 1 < right)
    {
      int mid = (left + right) / 2;
      if (check(mid))
      {
        right = mid;
      }
      else
      {
        left = mid;
      }
    }
    return right;
  }
};
