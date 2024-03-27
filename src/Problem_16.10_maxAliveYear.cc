#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 差分
  int maxAliveYear(vector<int>& birth, vector<int>& death)
  {
    vector<int> diff(2002);
    int n = birth.size();
    for (int i = 0; i < n; i++)
    {
      diff[birth[i]]++;
      diff[death[i] + 1]--;
    }
    int max = 0;
    int idx = 0;
    int sum = 0;
    for (int i = 1900; i <= 2000; i++)
    {
      sum += diff[i];
      if (max < sum)
      {
        max = sum;
        idx = i;
      }
    }
    return idx;
  }

  // 优先级队列
  int maxAliveYear2(vector<int>& birth, vector<int>& death)
  {
    int n = birth.size();
    vector<int> idx(n);
    for (int i = 0; i < n; i++)
    {
      idx[i] = i;
    }
    // 根据开始时间排序
    std::sort(idx.begin(), idx.end(), [&](int i, int j) { return birth[i] < birth[j]; });
    priority_queue<int, vector<int>, greater<int>> q;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      // 注意这里不能取等号 death[q.top()] <= birth[idx[i]]
      // 题设生于 1908 年、死于 1909 年的人应当被列入 1908 年和 1909 年的计数
      while (!q.empty() && death[q.top()] < birth[idx[i]])
      {
        q.pop();
      }
      ans = std::max(ans, (int) q.size());
      q.push(death[idx[i]]);
    }
    return ans;
  }
};
