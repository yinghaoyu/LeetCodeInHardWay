#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  int minimumRounds(vector<int>& tasks)
  {
    std::sort(tasks.begin(), tasks.end());
    int ans = 0;
    int diff = 0;
    int n = tasks.size();
    for (int i = 0; i < n; i++)
    {
      if (i == 0 || tasks[i - 1] == tasks[i])
      {
        // 统计相同的数，当然用 unordered_map 缓存也可
        diff++;
      }
      else
      {
        if (diff < 2)
        {
          return -1;
        }
        ans += (diff + 3 - 1) / 3;
        diff = 1;
      }
    }
    // 计算最后一个相同的数
    if (diff < 2)
    {
      return -1;
    }
    ans += (diff + 3 - 1) / 3;
    return ans;
  }
};
