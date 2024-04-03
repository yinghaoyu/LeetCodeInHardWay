#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> shortestSeq(vector<int>& big, vector<int>& small)
  {
    int n = big.size();
    unordered_map<int, int> cnt;
    int diff = 0;
    for (auto& num : small)
    {
      // 统计每个数出现的次数，题设每个数都是唯一的
      cnt[num]++;
      // 统计多少个不同的数
      diff++;
    }

    int l = 0;
    int r = 0;
    int min = n;
    vector<int> ans;
    while (r < n)
    {
      // 左边的数进来
      if (cnt.count(big[r]) && --cnt[big[r]] == 0)
      {
        --diff;
      }
      while (diff == 0)
      {
        if (r - l < min)
        {
          min = r - l;
          ans = {l, r};
        }
        // 右边的数出去
        if (cnt.count(big[l]) && ++cnt[big[l]] > 0)
        {
          ++diff;
        }
        ++l;
      }
      ++r;
    }
    return ans;
  }
};
