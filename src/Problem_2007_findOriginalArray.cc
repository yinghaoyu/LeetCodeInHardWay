#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> findOriginalArray(vector<int>& changed)
  {
    int n = changed.size();
    vector<int> ans;
    if (n & 1)
    {
      return ans;
    }
    std::sort(changed.begin(), changed.end());
    unordered_map<int, int> cnt;

    for (int num : changed)
    {
      cnt[num]++;
    }
    for (int num : changed)
    {
      if (cnt[num] == 0)
      {
        continue;
      }
      cnt[num]--;
      if (cnt[num * 2] == 0)
      {
        // 每个相同的数都必须有2倍数对应
        // {1, 1, 2, 4,}
        // 两个 1，只有一个 2，显然不行
        return {};
      }
      cnt[num * 2]--;
      ans.push_back(num);
    }
    return ans;
  }
};
