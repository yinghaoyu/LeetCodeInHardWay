#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  int maxEnvelopes(vector<vector<int>>& envelopes)
  {
    int n = envelopes.size();
    // 排序策略:
    // 宽度从小到大
    // 宽度一样，高度从大到小
    std::sort(envelopes.begin(), envelopes.end(),
              [](auto& lhs, auto& rhs)
              { return lhs[0] != rhs[0] ? lhs[0] < rhs[0] : lhs[1] > rhs[1]; });
    vector<int> ends(n);
    int len = 0;
    for (int i = 0, find, num; i < n; i++)
    {
      num = envelopes[i][1];
      find = bs(ends, len, num);
      if (find == -1)
      {
        ends[len++] = num;
      }
      else
      {
        ends[find] = num;
      }
    }
    return len;
  }

  int bs(vector<int>& ends, int len, int num)
  {
    int l = 0, r = len - 1, m, ans = -1;
    while (l <= r)
    {
      m = (l + r) / 2;
      if (ends[m] >= num)
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
