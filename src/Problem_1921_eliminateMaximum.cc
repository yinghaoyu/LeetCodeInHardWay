#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  int eliminateMaximum(vector<int>& dist, vector<int>& speed)
  {
    int n = dist.size();
    vector<int> time(n);
    for (int i = 0; i < n; i++)
    {
      // a / b向上取整 (a+b-1) / b;
      time[i] = (dist[i] + speed[i] - 1) / speed[i];
    }
    std::sort(time.begin(), time.end());
    for (int i = 0; i < n; i++)
    {
      // 每个怪物到达的时间 <= 累计耗时，说明怪物到达了城市
      if (time[i] <= i)
      {
        return i;
      }
    }
    return n;
  }
};
